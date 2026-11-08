function checkExecutableSkill_HolyFlash(obj)
{
	if (!obj) return false;
	local isUse = obj.sq_IsUseSkill(SKILL_HOLY_FLASH);
	if (isUse)
	{
		obj.sq_AddSetStatePacket(STATE_HOLY_FLASH, STATE_PRIORITY_IGNORE_FORCE, true);
		return true;
	}
	return false;
}

function checkCommandEnable_HolyFlash(obj)
{
	if (!obj) return false;
	local state = obj.sq_GetState();
	if (state == STATE_STAND)
		return true;
		return true;
}

function onSetState_HolyFlash(obj, state, datas, isResetTimer)
{
	if(!obj) return;
	obj.sq_StopMove();
	obj.sq_SetStaticSpeedInfo(SPEED_TYPE_CAST_SPEED, SPEED_TYPE_CAST_SPEED, SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);
	obj.sq_SetCurrentAnimation(CUSTOM_ANI_HOLY_FLASH_BODY);
}

function onKeyFrameFlag_HolyFlash(obj,flagIndex)
{
	if(!obj)
		return false;
	if (flagIndex == 5)
	{
		obj.sq_StartWrite();
		obj.sq_WriteDword(6);
		obj.sq_SendCreatePassiveObjectPacket(24240, 0, 20, -95, 0);
	}
	return true;
}

function onEndCurrentAni_HolyFlash(obj)
{
	obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
}
