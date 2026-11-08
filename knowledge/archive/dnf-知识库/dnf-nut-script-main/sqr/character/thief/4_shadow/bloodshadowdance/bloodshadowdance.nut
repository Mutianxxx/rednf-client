


function checkExecutableSkill_bloodshaowdancce(obj)  
{
	if (!obj) return false;
	local isUseSkill = obj.sq_IsUseSkill(SKILL_BLOOD_SHADOW_DANCE);
	if (isUseSkill) 
	{

		local pIntVec = sq_GetGlobalIntVector();
		sq_IntVectorClear(pIntVec);
		sq_IntVectorPush(pIntVec, 0);			
		obj.addSetStatePacket(STATE_BLOOD_SHADOW_DANCE , pIntVec,  STATE_PRIORITY_USER, false, "");

		return true;
	}

	return false;
}


function checkCommandEnable_bloodshaowdancce(obj)  
{

	return true;
}


