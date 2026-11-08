//////////////////////////////////////////////////////////////////////////////////////////////////
//									
//////////////////////////////////////////////////////////////////////////////////////////////////








function checkCommandEnable_bigkunai(obj)
{
	return true;
}



function checkExecutableSkill_bigkunai(obj)
{
	if(!obj) return false;
	
	local state = obj.sq_GetState();
	if(state == 3||state == 4||state == 5||state == 9||state == 16||state == 40) 
		return false;
	if(obj.sq_IsUseSkill(SKILL_BIGKUNAI))
	{
		local now_z = obj.getZPos();
		if(state == 6 || state == 7|| now_z>40)
		{
			obj.sq_IntVectClear();
			obj.sq_IntVectPush(1);
			obj.sq_AddSetStatePacket(STATE_BIGKUNAI, STATE_PRIORITY_IGNORE_FORCE, true);
			return true;
		}else{
			obj.sq_IntVectClear();
			obj.sq_IntVectPush(0);
			obj.sq_AddSetStatePacket(STATE_BIGKUNAI, STATE_PRIORITY_IGNORE_FORCE, true);
			return true;
		}
		
	}
	
	return false;
}



function onSetState_bigkunai(obj, state, datas, isResetTimer)
{	
	if(!obj) return;

	local subState = obj.sq_GetVectorData(datas, 0);
	obj.setSkillSubState(subState);
	obj.sq_StopMove();
	obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED,SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);
	switch(subState)
	{
		case 0:
			obj.sq_SetCurrentAnimation(CUSTOM_ANI_BIGKUNAI1);
			obj.sq_PlaySound("R_TF_NSKUNAI");
		break;
		case 1:
			obj.sq_SetCurrentAnimation(CUSTOM_ANI_BIGKUNAI2);
			obj.sq_ZStop();
			obj.sq_PlaySound("R_TF_NSKUNAI");
		break;
	}
}



function onEndCurrentAni_bigkunai(obj)
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
		case 1:
			obj.sq_IntVectClear();
			obj.sq_IntVectPush(1);
			obj.sq_IntVectPush(0);
			obj.sq_IntVectPush(0);
			obj.sq_AddSetStatePacket(STATE_JUMP, STATE_PRIORITY_IGNORE_FORCE, true);
		break;
	}
}



function onAfterSetState_bigkunai(obj, state, datas, isResetTimer)
{
	if(!obj) return;

	local subState = obj.sq_GetVectorData(datas, 0);
	switch(subState)
	{
		case 0:
			if(obj.isMyControlObject())
			{
				obj.sq_StartWrite();
				obj.sq_WriteDword(10);
				obj.sq_SendCreatePassiveObjectPacket(24356, 0, 0, 0, 0);
			}
		break;
		case 1:
			if(obj.isMyControlObject())
			{
				obj.sq_StartWrite();
				obj.sq_WriteDword(11);
				obj.sq_SendCreatePassiveObjectPacket(24356, 0, 0, 0, 0);
			}
		break;
	}
}

