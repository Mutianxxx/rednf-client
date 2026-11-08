//////////////////////////////////////////////////////////////////////////////////////////////////
//									
//////////////////////////////////////////////////////////////////////////////////////////////////








function checkCommandEnable_flametornado(obj)
{

	return true;
}



function checkExecutableSkill_flametornado(obj)
{
	if(!obj) return false;
	local isUse = obj.sq_IsUseSkill(SKILL_FLAMETORNADO);
	if(isUse)
	{
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(0);
		obj.sq_AddSetStatePacket(STATE_FLAMETORNADO, STATE_PRIORITY_IGNORE_FORCE, true);
		return true;
	}
	return false;
}




function onSetState_flametornado(obj, state, datas, isResetTimer)
{	
	if(!obj) return;

	local subState = obj.sq_GetVectorData(datas, 0);
	obj.setSkillSubState(subState);
	obj.sq_StopMove();
	obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED,SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);
	switch(subState)
	{
		case 0:
			obj.sq_SetCurrentAnimation(CUSTOM_ANI_FLAMETORNADO);
			obj.sq_PlaySound("R_TF_FLAMETORNADO");
		break;
	}
}



function onEndCurrentAni_flametornado(obj)
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



function onAfterSetState_flametornado(obj, state, datas, isResetTimer)
{
	if(!obj) return;

	local subState = obj.sq_GetVectorData(datas, 0);
	switch(subState)
	{
		case 0:
			if(obj.isMyControlObject())
			{
				obj.sq_StartWrite();
				obj.sq_WriteDword(8);
				obj.sq_SendCreatePassiveObjectPacket(24356, 0, 0, 0, -sq_GetZPos(obj));
			}
		break;
	}
}


