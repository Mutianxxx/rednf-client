function checkCommandEnable_ShakeDown(obj)
{
	if(!obj)
		return false;
	return true;
}


function checkExecutableSkill_ShakeDown(obj)
{
	if(!obj)
		return false;

	local isUse = obj.sq_IsUseSkill(SKILL_SHAKE_DOWN);

	if(isUse)
	{
		obj.sq_AddSetStatePacket(STATE_SHAKE_DOWN, STATE_PRIORITY_USER, false);

		return true;
	}

	return false;
}


function onSetState_ShakeDown(obj, state, datas, isResetTimer)
{
	if(!obj)
		return;

	obj.sq_StopMove();
	obj.sq_SetCurrentAnimation(135);
	obj.sq_SetStaticSpeedInfo(SPEED_TYPE_CAST_SPEED, SPEED_TYPE_CAST_SPEED, SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);
}


function onKeyFrameFlag_ShakeDown(obj, flagIndex)
{
	if(!obj)
		return false;

	if(obj.isMyControlObject() && flagIndex == 10001)
	{
		local skillLevel = sq_GetSkillLevel(obj, SKILL_SHAKE_DOWN);
		local skillTime = sq_GetLevelData(obj, SKILL_SHAKE_DOWN, 0, skillLevel);
		local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, SKILL_SHAKE_DOWN, false, "Character/Thief/ShakeDown/ap_ShakeDown.nut", false);

		appendage.sq_SetValidTime(skillTime);
		appendage.setAppendCauseSkill(BUFF_CAUSE_SKILL, sq_getJob(obj), SKILL_SHAKE_DOWN, skillLevel);
		CNSquirrelAppendage.sq_Append(appendage, obj, obj);
	}

	return true;
}


function onEndCurrentAni_ShakeDown(obj)
{
	obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
}

