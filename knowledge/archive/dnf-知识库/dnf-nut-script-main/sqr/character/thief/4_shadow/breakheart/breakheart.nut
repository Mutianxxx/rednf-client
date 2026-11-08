
function checkExecutableSkill_breakheart(obj)  
{
	if (!obj) return false;

	local isUseSkill = obj.sq_IsUseSkill(SKILL_BREAK_HEART);
	if (isUseSkill) 
	{

		local pIntVec = sq_GetGlobalIntVector();
		sq_IntVectorClear(pIntVec);
		sq_IntVectorPush(pIntVec, 0);			
		obj.addSetStatePacket(STATE_BREAK_HEART , pIntVec,  STATE_PRIORITY_USER, false, "");

		return true;
	}

	return false;
}


function checkCommandEnable_breakheart(obj)  
{

	return true;
}
