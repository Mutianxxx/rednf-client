
function checkExecutableSkill_severshaowslash(obj)  
{
	if (!obj) return false;

	local isUseSkill = obj.sq_IsUseSkill(SKILL_SEVER_SHADOW_SLASH);
	if (isUseSkill) 
	{
		local pIntVec = sq_GetGlobalIntVector();
		sq_IntVectorClear(pIntVec);
		sq_IntVectorPush(pIntVec, 0);			
		obj.addSetStatePacket(STATE_SEVER_SHADOW_SLASH , pIntVec,  STATE_PRIORITY_USER, false, "");
		return true;
	}

	return false;
}




function checkCommandEnable_severshaowslash(obj)  
{
	return true;
}

