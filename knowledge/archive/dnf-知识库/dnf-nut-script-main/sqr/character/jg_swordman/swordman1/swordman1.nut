function checkExecutableSkill_SwordMan1(obj)  
{
	if (!obj) return false;
	local isUse = obj.sq_IsUseSkill(SKILL_SWORDMAN1);

	if (isUse) {
		obj.sq_AddSetStatePacket(STATE_SWORDMAN1 , STATE_PRIORITY_USER, false);
		return true;
	}

	return false;
}


function checkCommandEnable_SwordMan1(obj)
{
	if (!obj) return false;
	local state = obj.sq_GetState();
	

	if (state == STATE_STAND)
		return true;
		
	if(state == STATE_ATTACK)
	{
		return obj.sq_IsCommandEnable(SKILL_SWORDMAN1); 
	}	

	return true;
}


function onSetState_SwordMan1(obj, state, datas, isResetTimer)
{	
	if(!obj) return;
	obj.sq_StopMove();
	obj.sq_SetCurrentAnimation(CUSTOM_ANI_ATTACK);
}

function onEndCurrentAni_SwordMan1(obj)
{
	obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
}
