//////////////////////////////////////////////////////////////////////////////////////////////////
//									
//////////////////////////////////////////////////////////////////////////////////////////////////








function checkCommandEnable_doomfield(obj)
{

	return true;
}



function checkExecutableSkill_doomfield(obj)
{
	if(!obj) return false;

	local isUse = obj.sq_IsUseSkill(SKILL_DOOMFIELD);
	if(isUse)
	{
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(0);
		obj.sq_AddSetStatePacket(STATE_DOOMFIELD, STATE_PRIORITY_IGNORE_FORCE, true);
		return true;
	}
	return false;
}



function onSetState_doomfield(obj, state, datas, isResetTimer)
{	
	if(!obj) return;

	local subState = obj.sq_GetVectorData(datas, 0);
	obj.setSkillSubState(subState);
	obj.sq_StopMove();
	obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED,SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);
	switch(subState)
	{
		case 0:
			obj.sq_SetCurrentAnimation(CUSTOM_ANI_DOOMFIELD);
			obj.sq_PlaySound("R_TF_NINPOJIN_01");
		break;
	}
}



function onEndCurrentAni_doomfield(obj)
{
	if(!obj) return;

	if(!obj.isMyControlObject())
	{
		return;
	}

	local subState = obj.getSkillSubState();
	switch(subState)
	{
		case 0:
			obj.sq_IntVectClear();
			obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_IGNORE_FORCE, true);
		break;
	}
}



function onAfterSetState_doomfield(obj, state, datas, isResetTimer)
{
	if(!obj) return;

	local subState = obj.getSkillSubState();
	switch(subState)
	{
		case 0:
			if(obj.isMyControlObject())
			{
				obj.sq_StartWrite();
				obj.sq_WriteDword(30);
				obj.sq_SendCreatePassiveObjectPacket(24356, 0, 0, 0, -sq_GetZPos(obj));
			}
		break;
	}
}



function onKeyFrameFlag_doomfield(obj, flagIndex)
{
	if(!obj) return false;

	local subState = obj.getSkillSubState();
	switch(subState)
	{
		case 0:
			switch(flagIndex)
			{
				case 10001:
					sq_MoveToNearMovablePos(obj, sq_GetDistancePos(sq_GetXPos(obj), obj.getDirection(), 400), sq_GetYPos(obj), sq_GetZPos(obj), sq_GetXPos(obj), sq_GetYPos(obj), sq_GetZPos(obj), 20, -1, 3);
				break;
			}
		break;
	}
	return true;
}

