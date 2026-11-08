function checkExecutableSkill_BloodStinger(obj)
{
	if (!obj) return false;
	local isUse = obj.sq_IsUseSkill(SKILL_BLOODSTINGER);

	if (isUse) {
		obj.sq_AddSetStatePacket(STATE_BLOODSTINGER, STATE_PRIORITY_USER, false);
		return true;
	}

	return false;
}


function checkCommandEnable_BloodStinger(obj)
{
	if (!obj) return false;
	local state = obj.sq_GetState();

    if (judgeSubBloodValue(obj,obj.sq_GetIntData(SKILL_BLOODSTINGER, 9)))
    return false;

	if (state == STATE_STAND)
		return true;

	if (state == STATE_ATTACK)
	{
		return obj.sq_IsCommandEnable(SKILL_BLOODSTINGER);
	}
	return true;
}


function onSetState_BloodStinger(obj, state, datas, isResetTimer)
{
	if (!obj) return;
	obj.sq_StopMove();
	setBloodValue(obj,-obj.sq_GetIntData(SKILL_BLOODSTINGER, 9));
	obj.sq_SetCurrentAnimation(CUSTOM_ANI_ATBLOODSTINGE_BODY);
	obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED,
		SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);
}

function onEndCurrentAni_BloodStinger(obj)
{
	obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
}


function onKeyFrameFlag_BloodStinger(obj, flagIndex)
{
	if (!obj)
		return false;

	local isMyControlObject = obj.sq_IsMyControlObject();

	if (isMyControlObject && flagIndex == 1)
	{
		obj.sq_PlaySound("BLOODSTINGE_CAST");//播放聲音

		local attackBonusRate = obj.sq_GetBonusRateWithPassive(SKILL_BLOODSTINGER, STATE_BLOODSTINGER, 0, 1.0);

		obj.sq_StartWrite();
		obj.sq_WriteDword(attackBonusRate);
		obj.sq_SendCreatePassiveObjectPacket(24345, 0, 0, 1, 0);
	}
	else if (isMyControlObject && flagIndex == 2)
	{
		sq_SetMyShake(obj, 7, 40);
		sq_flashScreen(obj, 240, 360, 150, 255, sq_RGB(0, 0, 0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
	}
	else if (isMyControlObject && flagIndex == 3)
	{
		sq_SetMyShake(obj, 30, 250);
		sq_flashScreen(obj, 0, 80, 280, 127, sq_RGB(255, 0, 0), GRAPHICEFFECT_LINEARDODGE, ENUM_DRAWLAYER_COVER);
	}
	else if (isMyControlObject && flagIndex == 4)
	{
		local pooledObj = sq_AddDrawOnlyAniFromParent(obj,"character/mage/effect/animation/atbloodstinger/atbloodstingeback_22.ani", 0, -1, 0);
	}
	return true;
}