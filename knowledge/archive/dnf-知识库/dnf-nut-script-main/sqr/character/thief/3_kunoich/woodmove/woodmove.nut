//////////////////////////////////////////////////////////////////////////////////////////////////
//									
//////////////////////////////////////////////////////////////////////////////////////////////////








function checkCommandEnable_woodmove(obj)
{
	return true;
}



function checkExecutableSkill_woodmove(obj)
{
	if(!obj) return false;

	
	local state = obj.sq_GetState();
	if(state == 3||state == 4||state == 5||state == 9||state == 16||state == 40) 
		return false;
	if(obj.sq_IsUseSkill(SKILL_WOODMOVE))
	{
		local now_z = obj.getZPos();
		if(state == 6 || state == 7 || now_z>50)
		{
			obj.sq_IntVectClear();
			obj.sq_IntVectPush(1);
			obj.sq_AddSetStatePacket(STATE_WOODMOVE, STATE_PRIORITY_IGNORE_FORCE, true);
			return true;
		}else{
			obj.sq_IntVectClear();
			obj.sq_IntVectPush(0);
			obj.sq_AddSetStatePacket(STATE_WOODMOVE, STATE_PRIORITY_IGNORE_FORCE, true);
			return true;
		}
		
	}
	return false;
}



function onSetState_woodmove(obj, state, datas, isResetTimer)
{	
	if(!obj) return;

	local subState = obj.sq_GetVectorData(datas, 0);
	obj.setSkillSubState(subState);
	obj.sq_StopMove();
	obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED,SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);
	switch(subState)
	{
		case 0:
			obj.sq_SetCurrentAnimation(CUSTOM_ANI_WOODMOVE1);
			local xDistance = sq_GetDistancePos(sq_GetXPos(obj), obj.getDirection(), sq_GetIntData(obj, SKILL_WOODMOVE, 0));
			obj.getVar("woodMove").clear_vector();
			obj.getVar("woodMove").push_vector(xDistance);
		break;
		case 1:
			obj.sq_SetCurrentAnimation(CUSTOM_ANI_WOODMOVE2);
			obj.sq_ZStop();
			local zDistance = 0;
			obj.getVar("woodMove").clear_vector();
			obj.getVar("woodMove").push_vector(zDistance);
		break;
	}
}



function onEndCurrentAni_woodmove(obj)
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
			obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_IGNORE_FORCE, true);
		break;
	}
}



function onProc_woodmove(obj)
{
	if(!obj) return;

	local subState = obj.getSkillSubState();
	local pAni = obj.getCurrentAnimation();
	local currentT = sq_GetCurrentTime(pAni);
	switch(subState)
	{
		case 0:
			local xDistance = obj.getVar("woodMove").get_vector(0);
			local xAccel = sq_GetUniformVelocity(sq_GetXPos(obj), xDistance, currentT, 100);
			sq_setCurrentAxisPos(obj, 0, xAccel);
			sq_SimpleMoveToNearMovablePos(obj, sq_GetIntData(obj, SKILL_WOODMOVE, 0));
		break;
		case 1:
			local zDistance = obj.getVar("woodMove").get_vector(0);
			local zAccel = sq_GetUniformVelocity(sq_GetZPos(obj), zDistance, currentT, 100);
			sq_setCurrentAxisPos(obj, 2, zAccel);
			sq_SimpleMoveToNearMovablePos(obj, sq_GetIntData(obj, SKILL_WOODMOVE, 0));
		break;
	}
}

