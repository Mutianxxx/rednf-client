function checkExecutableSkill_ProtectionOfUriel(obj)
{
	if (!obj) return false;
	local isUse = obj.sq_IsUseSkill(SKILL_PROTECTION_OF_URIEL);
	if (isUse)
	{
		if(obj.sq_GetState() == STATE_ARIA_OF_COURAGE || obj.sq_GetState() == STATE_ARIA_OF_REGENERATION)
		{
			obj.sq_PlaySound("URIEL_CAST");
			obj.sq_StartWrite();
			obj.sq_WriteDword(29);
			obj.sq_SendCreatePassiveObjectPacket(24240, 0, 0, 0, 0);
		}else{
			obj.sq_AddSetStatePacket(STATE_PROTECTION_OF_URIEL, STATE_PRIORITY_IGNORE_FORCE, true);
			return true;
		}
	}
	return false;
}

function checkCommandEnable_ProtectionOfUriel(obj)
{
	if (!obj) return false;
		return true;
}

function onSetState_ProtectionOfUriel(obj, state, datas, isResetTimer)
{
	if(!obj) return;
	obj.sq_StopMove();
	obj.sq_SetStaticSpeedInfo(SPEED_TYPE_CAST_SPEED, SPEED_TYPE_CAST_SPEED, SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);
	obj.sq_SetCurrentAnimation(CUSTOM_ANI_PROTECTION_OF_URIEL_CAST_BODY);
	obj.sq_StartWrite();
	obj.sq_WriteDword(29);
	obj.sq_SendCreatePassiveObjectPacket(24240, 0, 0, 0, 0);
}

function onKeyFrameFlag_ProtectionOfUriel(obj,flagIndex)
{
	if(!obj)
		return false;
	if (flagIndex == 0)
	{
		obj.sq_PlaySound("URIEL_CAST");
	}
	if (flagIndex == 1)
	{
		sq_flashScreen(obj, 0, 60, 120, 63, sq_RGB(255,255,255), GRAPHICEFFECT_LINEARDODGE, ENUM_DRAWLAYER_COVER);
	}
	return true;
}

function onEndCurrentAni_ProtectionOfUriel(obj)
{
	obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);

}










