
function checkExecutableSkill_shaowwipe(obj)  
{
	if (!obj) return false;


	local isUseSkill = obj.sq_IsUseSkill(SKILL_SHADOW_WIPE);
	if (isUseSkill) 
		{
		
			local pIntVec = sq_GetGlobalIntVector();
			sq_IntVectorClear(pIntVec);
			sq_IntVectorPush(pIntVec, 0);			
			obj.addSetStatePacket(STATE_SHADOW_WIPE , pIntVec,  STATE_PRIORITY_USER, false, "");

			return true;
		}
	return false;
}


function checkCommandEnable_shaowwipe(obj)  
{

	return true;
}
