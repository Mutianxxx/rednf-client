
function checkExecutableSkill_Inquisitor(obj)
{
	if(!obj)
		return false;

	local isUse = obj.sq_IsUseSkill(SKILL_Inquisitor);
	if (isUse)
	{
		obj.sq_AddSetStatePacket(STATE_Inquisitor, STATE_PRIORITY_USER, false);
		return true;
	}
	return false;
}


function checkCommandEnable_Inquisitor(obj)
{
	if (!obj)
		return false;

	local state = obj.sq_GetState();
	if (state == STATE_STAND)
	
		return true;

	return true;
}

function onEndCurrentAni_Inquisitor(obj)
{
	local substate = obj.getSkillSubState();

	if(substate == 0)
	{
		obj.getVar().clear_vector();
		obj.getVar().push_vector(1);
		obj.sq_AddSetStatePacket(STATE_Inquisitor ,STATE_PRIORITY_USER, true);
	}
	else if(substate == 1)
	{
		obj.getVar().clear_vector();
		obj.getVar().push_vector(2);
		obj.sq_AddSetStatePacket(STATE_Inquisitor, STATE_PRIORITY_USER, true);
	}
	else if(substate == 2)
	{
		obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
	}
}
