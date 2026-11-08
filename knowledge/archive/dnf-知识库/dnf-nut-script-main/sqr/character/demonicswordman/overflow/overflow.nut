function checkExecutableSkill_overflow(obj)
{
	if (!obj) return false;
	local isUse = obj.sq_IsUseSkill(SKILL_OVERFLOW);
	
	if (isUse)
	{
		obj.sq_AddSetStatePacket(STATE_OVERFLOW , STATE_PRIORITY_USER, false);
		return true;
	}
	
	return false;
}

function checkCommandEnable_overflow(obj)
{
	if (!obj) return false;
	local state = obj.sq_GetState();
	
	if (state == STATE_STAND)
		return true;

	return true;

}

function onSetState_overflow(obj, state, datas, isResetTimer)
{	
	if(!obj) return;
	
	obj.sq_StopMove();
	obj.sq_SetCurrentAnimation(CUSTOM_ANI_OVERFLOW_BODY);
	obj.sq_SetStaticSpeedInfo(SPEED_TYPE_CAST_SPEED, SPEED_TYPE_CAST_SPEED,
	SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);	
}



function onAttack_overflow(obj, damager, boundingBox, isStuck)
{
	if (!obj) return;

}

function onKeyFrameFlag_overflow(obj,flagIndex)
{
	if(!obj)
		return false;
	if (flagIndex == 1)
	{
		local skill_level = sq_GetSkillLevel(obj, SKILL_OVERFLOW);

		local skillTime = sq_GetLevelData(obj, SKILL_OVERFLOW, 1, skill_level);

		local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, SKILL_OVERFLOW, false,"character/demonicswordman/overflow/ap_overflow.nut", false);

		appendage.setAppendCauseSkill(BUFF_CAUSE_SKILL, sq_getJob(obj), SKILL_OVERFLOW, skill_level);
		
		CNSquirrelAppendage.sq_AppendAppendageID(appendage, obj, obj, STATE_OVERFLOW, true);
		
		appendage = obj.GetSquirrelAppendage("character/demonicswordman/overflow/ap_overflow.nut");
		if(skillTime>0)
			appendage.sq_SetValidTime(skillTime);
		appendage.setBuffIconImage(138);//sprite_common_commoneffect.NPK
		if(appendage)
		{
			local value0 = sq_GetLevelData(obj, SKILL_OVERFLOW, 2, skill_level); 
			local value1 = sq_GetLevelData(obj, SKILL_OVERFLOW, 2, skill_level); 
			//local value2 = sq_GetLevelData(obj, SKILL_OVERFLOW, 3, skill_level); 
			local value3 = sq_GetLevelData(obj, SKILL_OVERFLOW, 0, skill_level)/10; 
			local value4 = sq_GetLevelData(obj, SKILL_OVERFLOW, 0, skill_level)/10; 
			local change_appendage = appendage.sq_getChangeStatus("overflow");
			if(!change_appendage)
			{
				change_appendage = appendage.sq_AddChangeStatus("overflow",obj, obj, 0, CHANGE_STATUS_TYPE_ADDITIONAL_PHYSICAL_GENUINE_ATTACK, true, 0);
			}
			if(change_appendage)
			{
				change_appendage.clearParameter();
				change_appendage.addParameter(CHANGE_STATUS_TYPE_EQUIPMENT_PHYSICAL_ATTACK, true, value0.tofloat());
				change_appendage.addParameter(CHANGE_STATUS_TYPE_EQUIPMENT_MAGICAL_ATTACK, true, value1.tofloat());
				//change_appendage.addParameter(CHANGE_STATUS_TYPE_ADDITIONAL_PHYSICAL_GENUINE_ATTACK, false, value2.tofloat());
				change_appendage.addParameter(CHANGE_STATUS_TYPE_PHYSICAL_CRITICAL_DAMAGE_RATE, false, value3.tofloat());
				change_appendage.addParameter(CHANGE_STATUS_TYPE_MAGICAL_CRITICAL_DAMAGE_RATE, false, value4.tofloat());
			}
		}
	}

	return true;
}



function onEndCurrentAni_overflow(obj)
{
	obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
}
