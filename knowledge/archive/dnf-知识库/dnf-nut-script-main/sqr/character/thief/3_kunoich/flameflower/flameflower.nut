//////////////////////////////////////////////////////////////////////////////////////////////////
//									
//////////////////////////////////////////////////////////////////////////////////////////////////








function checkCommandEnable_flameflower(obj)
{

	return true;
}



function checkExecutableSkill_flameflower(obj)
{
	if(!obj) return false;
	local now_z = obj.getZPos();
	if(now_z>1){
		return false;
	}
	local isUse = obj.sq_IsUseSkill(SKILL_FLAMEFLOWER);
	if(isUse)
	{
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(0);
		obj.sq_AddSetStatePacket(STATE_FLAMEFLOWER, STATE_PRIORITY_IGNORE_FORCE, true);
		return true;
	}
	return false;
}



function onSetState_flameflower(obj, state, datas, isResetTimer)
{	
	if(!obj) return;

	local subState = obj.sq_GetVectorData(datas, 0);
	obj.setSkillSubState(subState);
	obj.sq_StopMove();
	obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED,SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);
	switch(subState)
	{
		case 0:
			local ani = sq_CreateAnimation("","character/thief/animation/flameflower.ani");
			obj.setCurrentAnimation(ani);
		break;
	}
}



function onEndCurrentAni_flameflower(obj)
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



function onAfterSetState_flameflower(obj, state, datas, isResetTimer)
{
	if(!obj) return;

	local subState = obj.sq_GetVectorData(datas, 0);
	switch(subState)
	{
		case 0:
			if(obj.isMyControlObject())
			{
				obj.sq_StartWrite();
				obj.sq_WriteDword(27);
				obj.sq_SendCreatePassiveObjectPacket(24356, 0, 0, -1, 0);
			}
		break;
	}
}



function onProc_flameflower(obj)
{
	if(!obj) return;

	local subState = obj.getSkillSubState();
	local pAni = obj.getCurrentAnimation();
	local frameIndex = sq_GetAnimationFrameIndex(pAni);
	switch(subState)
	{
		case 0:
			if(frameIndex <= 31)
			{
				sq_SetKeyxEnable(obj, E_JUMP_COMMAND, true);
				if(sq_IsEnterCommand(obj, E_JUMP_COMMAND))
				{
					sq_SetAnimationFrameIndex(pAni, 32);
				}
			}
			if(frameIndex >= 33 && frameIndex <= 66)
			{
				sq_SetKeyxEnable(obj, E_JUMP_COMMAND, true);
				if(sq_IsEnterCommand(obj, E_JUMP_COMMAND))
				{
					sq_SetAnimationFrameIndex(pAni, 67);
				}
			}
		break;
	}
}

