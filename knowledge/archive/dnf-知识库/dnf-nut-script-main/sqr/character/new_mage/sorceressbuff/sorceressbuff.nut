
//buff?b???i???s???e???U?W?L????100??A????C??N?|???1%??hp        8 ok
//cast flag 1  start 
//start flag 2 stop move
//CAST flag 2 add happy party




function checkExecutableSkill_sorceressbuff(obj)  
{
	if (!obj) return false;

	local isUseSkill = obj.sq_IsUseSkill(SKILL_SORCERESSBUFF);
	if (isUseSkill) 
	{
		obj.getVar("state").clear_vector();
		obj.getVar("state").push_vector(0);
		obj.sq_AddSetStatePacket(STATE_SORCERESSBUFF , STATE_PRIORITY_USER, true);
		return true;
	}

}


function checkCommandEnable_sorceressbuff(obj)
{
	return true;
}

function addSorceressBuff(obj)
{
	if (!obj) return;
	local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, SKILL_SORCERESSBUFF, false, "character/new_mage/sorceressbuff/ap_sorceressbuff_self.nut", false);

	local skill_level = sq_GetSkillLevel(obj, SKILL_SORCERESSBUFF);
	local time = sq_GetLevelData(obj, SKILL_SORCERESSBUFF, 0, skill_level);
	local stunAtkIncreate = sq_GetLevelData(obj, SKILL_SORCERESSBUFF, 7, skill_level);
	
	appendage.sq_SetValidTime(time);
	appendage.setAppendCauseSkill(BUFF_CAUSE_SKILL, ENUM_CHARACTERJOB_MAGE, SKILL_SORCERESSBUFF, skill_level);
	CNSquirrelAppendage.sq_AppendAppendageID(appendage, obj, obj, APID_SKILL_LIGHT_ENCHANT_WEAPON, false);
	appendage.setBuffIconImage(148);
	
	local change_appendage = appendage.sq_getChangeStatus("sorceressbuffself");
	if(!change_appendage)
	{
		change_appendage = appendage.sq_AddChangeStatus("sorceressbuffself",obj, obj, 0, 37, true, 0);
	}
	if (change_appendage)
	{
		change_appendage.clearParameter();
		change_appendage.addParameter(CHANGE_STATUS_TYPE_STUCK, false, -(stunAtkIncreate.tofloat() / 10) );
	}
}

function addSorceressFriendBuff(obj)
{
	if (!obj) return;
	local objectManager = obj.getObjectManager();
	local skill_level = sq_GetSkillLevel(obj, SKILL_SORCERESSBUFF);
	local time = sq_GetLevelData(obj, SKILL_SORCERESSBUFF, 0, skill_level);
	//local atkRate = sq_GetLevelData(obj, SKILL_SORCERESSBUFF, 1, skill_level);
	local wlAtkIncreate = sq_GetLevelData(obj, SKILL_SORCERESSBUFF, 2, skill_level);
	local mfAtkIncreate = sq_GetLevelData(obj, SKILL_SORCERESSBUFF, 3, skill_level);
	local dlAtkIncreate = sq_GetLevelData(obj, SKILL_SORCERESSBUFF, 4, skill_level);
	local llAtkIncreate = sq_GetLevelData(obj, SKILL_SORCERESSBUFF, 5, skill_level);
	local zlAtkIncreate = sq_GetLevelData(obj, SKILL_SORCERESSBUFF, 6, skill_level);
	local stunAtkIncreate = sq_GetLevelData(obj, SKILL_SORCERESSBUFF, 7, skill_level);
	local subTime = obj.sq_GetIntData(SKILL_SORCERESSBUFF, 1);
	for (local i = 0; i < objectManager.getCollisionObjectNumber(); i+=1)
	{
		local object = objectManager.getCollisionObject(i);

		if (object && !obj.isEnemy(object) && object.isObjectType(OBJECTTYPE_CHARACTER) && !isSameObject(obj, object))
		{
			object = sq_GetCNRDObjectToSQRCharacter(object);
			CNSquirrelAppendage.sq_RemoveAppendage(object, "character/new_mage/sorceressbuff/ap_sorceressbuff.nut");
			if (isFavoriteing(object))
			{
				wlAtkIncreate = wlAtkIncreate * 1.2;
				mfAtkIncreate = mfAtkIncreate * 1.2;
				dlAtkIncreate = dlAtkIncreate * 1.2;
				llAtkIncreate = llAtkIncreate * 1.2;
				zlAtkIncreate = zlAtkIncreate * 1.2;
				stunAtkIncreate = stunAtkIncreate * 1.2;
				subTime = 0;
			}
			local appendage = CNSquirrelAppendage.sq_AppendAppendage(object, obj, SKILL_SORCERESSBUFF, false, "character/new_mage/sorceressbuff/ap_sorceressbuff.nut", false);
			appendage.sq_SetValidTime(time );
			appendage.setAppendCauseSkill(BUFF_CAUSE_SKILL, ENUM_CHARACTERJOB_MAGE, SKILL_SORCERESSBUFF, skill_level);
			appendage.getVar("time").clear_vector();
			appendage.getVar("time").push_vector( subTime );
			appendage.getVar("time").push_vector( time );
			CNSquirrelAppendage.sq_AppendAppendageID(appendage, object, obj, APID_SKILL_LIGHT_ENCHANT_WEAPON, true);
			appendage.setBuffIconImage(148);
			
			local change_appendage = appendage.sq_getChangeStatus("sorceressbuff");
			if(!change_appendage)
			{
				change_appendage = appendage.sq_AddChangeStatusAppendageID(object, obj, 0, 37, false, 0, APID_COMMON);
			}
			if (change_appendage){
				change_appendage.clearParameter();
				change_appendage.addParameter(CHANGE_STATUS_TYPE_PHYSICAL_ATTACK, false, llAtkIncreate.tofloat());
				change_appendage.addParameter(CHANGE_STATUS_TYPE_MAGICAL_ATTACK, false, zlAtkIncreate.tofloat());
				change_appendage.addParameter(CHANGE_STATUS_TYPE_EQUIPMENT_PHYSICAL_ATTACK, false, wlAtkIncreate.tofloat());
				change_appendage.addParameter(CHANGE_STATUS_TYPE_EQUIPMENT_MAGICAL_ATTACK, false, mfAtkIncreate.tofloat());
				change_appendage.addParameter(CHANGE_STATUS_TYPE_STUCK, false, -(stunAtkIncreate.tofloat() / 10) );
			}
		}
	}
}


function onSetState_SORCERESSBUFF(obj, state, datas, isResetTimer)
{
	if (!obj) return;
	obj.sq_StopMove();
	local state = obj.getVar("state").get_vector(0);
	//obj.sq_SendCreatePassiveObjectPacket(24357, 0, 0, 1, 0);
	if (state == 0)
	{
		local skill_level = sq_GetSkillLevel(obj, SKILL_SORCERESSBUFF); 
		local castTime = sq_GetCastTime(obj, SKILL_SORCERESSBUFF, skill_level); 
		
		if (!isDollState(obj) )
		{
			obj.sq_SetCurrentAnimation(CUSTOM_ANI_SORCERESSBUFF_CASTING2);
		}
		else
		{
			local ani = obj.getVar().GetAnimationMap("sorceressCasting", "character/mage/animation/zrr_ani/favoritismcasting_mad_body.ani"); 
			obj.setCurrentAnimation(ani);
		}
		
		obj.getVar("isMove").clear_vector();
		obj.getVar("isMove").push_vector(0);
		sq_StartDrawCastGauge(obj, castTime, true); 
		//????
	}
	else if (state == 1)
	{
		addSorceressFriendBuff(obj);
		addSorceressBuff(obj);
		createSorceressBuffAuraEffect(obj);
		createSorceressBuffCircleEffect(obj);
		
		if (!isDollState(obj) )
		{
			obj.sq_SetCurrentAnimation(CUSTOM_ANI_SORCERESSBUFF_START2);
		}
		else
		{
			local ani = obj.getVar().GetAnimationMap("sorceressCasting", "character/mage/animation/zrr_ani/favoritismcastingafter_mad_body.ani"); 
			obj.setCurrentAnimation(ani);
		}
		obj.sq_SetStaticSpeedInfo(SPEED_TYPE_CAST_SPEED , SPEED_TYPE_CAST_SPEED , SPEED_VALUE_DEFAULT , SPEED_VALUE_DEFAULT , 1.0 , 1.0);
	}
	
	local ani = obj.sq_GetCurrentAni();
	local delay = ani.getDelaySum(false);
	obj.getVar("movValue").clear_vector();
	obj.getVar("movValue").push_vector(obj.getXPos() );
	obj.getVar("movValue").push_vector(delay);
	obj.getVar("movValue").push_vector( obj.sq_GetIntData(SKILL_SORCERESSBUFF, 2) );
}

function onEndState_SORCERESSBUFF(obj, state)
{
	if (!obj) return;
	local state = obj.getVar("state").get_vector(0);
	if (state == 0)
		sq_EndDrawCastGauge(obj);
}

function createSorceressBuffAuraEffect(obj)
{
	if (!obj) return;
	local ani = sq_CreateAnimation("","character/mage/animation/ani_als/forbiddencurse/aura_buff_03.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos(),obj.getZPos() );
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,0,false);	
}

function createSorceressBuffCircleEffect(obj)
{
	if (!obj) return;
	local ani = sq_CreateAnimation("","character/mage/animation/ani_als/forbiddencurse/curse_00.ani");
	local pooledObj = sq_CreatePooledObject(ani,true);
	pooledObj.setCurrentPos(obj.getXPos() ,obj.getYPos(),obj.getZPos() );
	pooledObj.setCurrentDirection(obj.getDirection());
	sq_AddObject(obj,pooledObj,0,false);	
}

function onProc_SORCERESSBUFF(obj)
{
	if (!obj) return;
	local state = obj.getVar("state").get_vector(0);
	local pAni = obj.sq_GetCurrentAni();
	local currentT = 0;
	if (state == 0)
	{
		currentT = sq_GetCurrentTime(pAni) - 6*80;
	}

	local startX = obj.getVar("movValue").get_vector(0);
	local delayT = obj.getVar("movValue").get_vector(1);
	local len = obj.getVar("movValue").get_vector(2);
	local v = sq_GetAccel(0, len, currentT, delayT, true);
	local dstX = sq_GetDistancePos(startX, obj.getDirection(), v);
	if(obj.isMovablePos(dstX, obj.getYPos() ) && obj.getVar("isMove").get_vector(0) == 1 )
	{
		sq_setCurrentAxisPos(obj, 0, dstX);
	}

}

function onKeyFrameFlag_SORCERESSBUFF(obj,flagIndex)
{
	if (!obj) return;
	local state = obj.getVar("state").get_vector(0);
	if (state == 0)
	{
		if (flagIndex == 3)
		{
			obj.getVar("isMove").clear_vector();
			obj.getVar("isMove").push_vector(1);
			//?}?l????
		}
	}
	else if (state == 1)
	{
		if (flagIndex == 2)
		{
			//??????
			obj.getVar("isMove").clear_vector();
			obj.getVar("isMove").push_vector(0);
		}
	}
}

function onEndCurrentAni_SORCERESSBUFF(obj)
{
	if (!obj) return;
	local state = obj.getVar("state").get_vector(0);
	if (state == 0)
	{
		obj.getVar("state").clear_vector();
		obj.getVar("state").push_vector(1);
		obj.sq_AddSetStatePacket(STATE_SORCERESSBUFF , STATE_PRIORITY_USER, true);
	}
	else if (state == 1)
	{
		obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
	}
}








