function checkExecutableSkill_ThunderOfCleans(obj)
{
	if (!obj) return false;
	local isUse = obj.sq_IsUseSkill(SKILL_THUNDER_OF_CLEANS);
	if (isUse)
	{
		obj.sq_AddSetStatePacket(STATE_THUNDER_OF_CLEANS, STATE_PRIORITY_IGNORE_FORCE, true);
		return true;
	}
	return false;
}

function checkCommandEnable_ThunderOfCleans(obj)
{
	if (!obj) return false;
	local state = obj.sq_GetState();
	if (state == STATE_STAND)
		return true;
		return true;
}

function onSetState_ThunderOfCleans(obj, state, datas, isResetTimer)
{
	if(!obj) return;
	local substate = obj.sq_GetVectorData(datas, 0);
	obj.setSkillSubState(substate);
	obj.sq_StopMove();
	local distance = sq_GetIntData(obj, SKILL_THUNDER_OF_CLEANS, SKL_INT_LV_0);
	obj.sq_SetCurrentAnimation(CUSTOM_ANI_ATTHUNDER_OF_CLEANS_START_BODY);
	obj.sq_SetStaticSpeedInfo(SPEED_TYPE_CAST_SPEED, SPEED_TYPE_CAST_SPEED, SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);
	sq_StartDrawCastGauge(obj, sq_GetCastTime(obj, SKILL_THUNDER_OF_CLEANS, sq_GetSkillLevel(obj, SKILL_THUNDER_OF_CLEANS)), true);
	obj.sq_StartWrite();
	obj.sq_WriteDword(23);
	obj.sq_SendCreatePassiveObjectPacket(24240, 0, distance, 0, 0);
}

function onEndState_ThunderOfCleans(obj, newState) {
	if(!obj)
		return false;
	if(newState != STATE_THUNDER_OF_CLEANS)
		sq_EndDrawCastGauge(obj);
}

function onKeyFrameFlag_ThunderOfCleans(obj,flagIndex)
{
	if(!obj)
		return false;

	return true;
}

function onEndCurrentAni_ThunderOfCleans(obj)
{
	local distance = sq_GetIntData(obj, SKILL_THUNDER_OF_CLEANS, SKL_INT_LV_0);
	obj.sq_StartWrite();
	obj.sq_WriteDword(24);
	obj.sq_SendCreatePassiveObjectPacket(24240, 0, distance - 20, 0, 0);
	obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
}

function getScrollBasisPos_ThunderOfCleans(obj)
{
	
	if(!obj) return;
	local substate = obj.getSkillSubState();
	if (obj.isMyControlObject())
	{
		local xPos = obj.getXPos();
		local distance = 250;
		local destX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), distance);
		local speedrate = 200;
		if(substate == 0)
		{
			local stateTimer = obj.sq_GetStateTimer();
			xPos = sq_GetUniformVelocity(xPos, destX, stateTimer, speedrate);
		}
		else
		{
			xPos = destX;
		}
		obj.sq_SetCameraScrollPosition(xPos, obj.getYPos(), 0);
		return true;
	}
	return false;
}