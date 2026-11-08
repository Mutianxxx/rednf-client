function checkExecutableSkill_bloodoctopussword(obj)
{
	if (!obj) return false;
	local isUse = obj.sq_IsUseSkill(SKILL_BLOODOCTOPUSSWORD);
	if (isUse)
	{
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(0);
		obj.sq_AddSetStatePacket(STATE_BLOODOCTOPUSSWORD, STATE_PRIORITY_IGNORE_FORCE, true);
		return true;
	}
	return false;
}

function checkCommandEnable_bloodoctopussword(obj)
{
	if (!obj) return false;
	local state = obj.sq_GetState();
	if (state == STATE_STAND)
		return true;
		return true;
}

function onSetState_bloodoctopussword(obj, state, datas, isResetTimer)
{
	if(!obj) return;
	local substate = obj.sq_GetVectorData(datas, 0);
	local sq_var = obj.getVar();
	obj.setSkillSubState(substate);
	obj.sq_StopMove();
	if(substate == 0)
	{
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_BloodOtopusSword_Body);
	}
	else if(substate == 1)
	{
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_Guard);
	}
}

function onEndCurrentAni_bloodoctopussword(obj)
{
	local substate = obj.getSkillSubState();
	local sq_var = obj.getVar();
	if(substate == 0)
	{
		obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
	}
	else if(substate == 1)
	{
		obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
	}
}

function onKeyFrameFlag_bloodoctopussword(obj,flagIndex)
{
	if(!obj)
	return false;
	if (flagIndex == 13)
	{
		ATSwordman_Als_Ani(obj, "passiveobject/atwordman/animation/atbloodoctopussword/bloodoctopusswordbottom_21.ani", 0, -1, 0, 0, 100, 0, 1.0);
	}
	if (flagIndex == 14)
	{
		sq_flashScreen(obj, 0, 40, 0, 125, sq_RGB(255,0,0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
		obj.sq_SetShake(obj,5,200);

		obj.sq_StartWrite();
		obj.sq_WriteDword(48);
		obj.sq_WriteDword(0);
		obj.sq_WriteDword(0);
		obj.sq_SendCreatePassiveObjectPacket(24239, 0, 5, -1, 0);
	}
	if (flagIndex == 16)
	{
		sq_flashScreen(obj, 0, 40, 0, 125, sq_RGB(255,255,255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
	}

	if (flagIndex == 19)
	{
		sq_flashScreen(obj, 0, 40, 0, 125, sq_RGB(255,0,0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
	}

	if (flagIndex == 35)
	{
		obj.sq_SetShake(obj,2,300);
	}
	if (flagIndex == 42)
	{
		sq_flashScreen(obj, 0, 40, 0, 125, sq_RGB(255,0,0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
		obj.sq_SetShake(obj,12,300);

		obj.sq_StartWrite();
		obj.sq_WriteDword(49);
		obj.sq_WriteDword(0);
		obj.sq_WriteDword(0);
		obj.sq_SendCreatePassiveObjectPacket(24239, 0, 5, -1, 0);
	}
	if (flagIndex == 44)
	{
		sq_flashScreen(obj, 0, 40, 0, 125, sq_RGB(255,255,255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
	}
	return true;
}

function getScrollBasisPos_bloodoctopussword(obj)
{
	if (!obj) return;
	local subState = obj.getSkillSubState();
	local pAni = obj.getCurrentAnimation();
	local frmIndex = sq_GetAnimationFrameIndex(pAni);
	if (obj.isMyControlObject())
	{
		local destX = sq_GetDistancePos(obj.getXPos(), obj.getDirection(), 250);
		local xPos = obj.getXPos();
		if (subState == 0)
		{
			local stateTimer = obj.sq_GetStateTimer();
			xPos = sq_GetUniformVelocity(xPos, destX, stateTimer, 200);
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