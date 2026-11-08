//////////////////////////////////////////////////////////////////////////////////////////////////
//									
//////////////////////////////////////////////////////////////////////////////////////////////////








function checkCommandEnable_migawari(obj)
{

	return true;
}



function checkExecutableSkill_migawari(obj)
{
	if(!obj) return false;
	local isUse = obj.sq_IsUseSkill(SKILL_MIGAWARI);
	if(isUse)
	{
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(0);
		obj.sq_AddSetStatePacket(STATE_MIGAWARI, STATE_PRIORITY_IGNORE_FORCE, true);
		return true;
	}
	return false;
}



function onSetState_migawari(obj, state, datas, isResetTimer)
{	
	if(!obj) return;

	local subState = obj.sq_GetVectorData(datas, 0);
	obj.setSkillSubState(subState);
	obj.sq_StopMove();
	obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED,SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);
	switch(subState)
	{
		case 0:
			obj.sq_SetCurrentAnimation(CUSTOM_ANI_MIGAWARI1);
			obj.sq_PlaySound("R_TF_MIGAWARI");
		break;
		case 1:
			obj.sq_SetCurrentAnimation(CUSTOM_ANI_MIGAWARI2);
			local xDistance = sq_GetDistancePos(sq_GetXPos(obj), obj.getDirection(), -200);
			local zDistance = 100;
			obj.getVar("migawariMove").clear_vector();
			obj.getVar("migawariMove").push_vector(xDistance);
			obj.getVar("migawariMove").push_vector(zDistance);
		break;
	}
}



function onEndCurrentAni_migawari(obj)
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
			obj.sq_IntVectPush(1);
			obj.sq_AddSetStatePacket(STATE_MIGAWARI, STATE_PRIORITY_IGNORE_FORCE, true);
		break;
		case 1:
			obj.sq_IntVectClear();
			obj.sq_IntVectPush(1);
			obj.sq_IntVectPush(0);
			obj.sq_IntVectPush(100);
			obj.sq_AddSetStatePacket(STATE_JUMP, STATE_PRIORITY_IGNORE_FORCE, true);
		break;
	}
}



function onAfterSetState_migawari(obj, state, datas, isResetTimer)
{
	if(!obj) return;

	local subState = obj.sq_GetVectorData(datas, 0);
	switch(subState)
	{
		case 0:
			if(obj.isMyControlObject())
			{
				obj.sq_StartWrite();
				obj.sq_WriteDword(14);
				obj.sq_SendCreatePassiveObjectPacket(24356, 0, 0, -1, 0);
			}
		break;
	}
}



function onProc_migawari(obj)
{
	if(!obj) return;

	local subState = obj.getSkillSubState();
	local pAni = obj.getCurrentAnimation();
	local currentT = sq_GetCurrentTime(pAni);
	switch(subState)
	{
		case 1:
			local xDistance = obj.getVar("migawariMove").get_vector(0);
			local zDistance = obj.getVar("migawariMove").get_vector(1);
			local xAccel = sq_GetUniformVelocity(sq_GetXPos(obj), xDistance, currentT, 1500);
			local zAccel = sq_GetUniformVelocity(sq_GetZPos(obj), zDistance, currentT, 500);
			sq_setCurrentAxisPos(obj, 0, xAccel);
			sq_setCurrentAxisPos(obj, 2, zAccel);
			sq_SimpleMoveToNearMovablePos(obj, 200);
		break;
	}
}

