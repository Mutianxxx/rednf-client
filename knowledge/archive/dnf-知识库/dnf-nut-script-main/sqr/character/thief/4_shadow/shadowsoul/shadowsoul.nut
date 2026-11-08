

function checkExecutableSkill_shaowsoul(obj)  
{
	if (!obj) return false;
	if (!CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/thief/4_shadow/shadowsoul/ap_shadowsoul.nut"))
	{

		local isUseSkill = obj.sq_IsUseSkill(SKILL_SHADOW_SOUL);
		if (isUseSkill) 
		{
			local pIntVec = sq_GetGlobalIntVector();
			sq_IntVectorClear(pIntVec);
			sq_IntVectorPush(pIntVec, 0);			
			obj.addSetStatePacket(STATE_SHADOW_SOUL , pIntVec,  STATE_PRIORITY_USER, false, "");

			return true;
		}
		return false;
	}else
	{
		local apd = obj.GetSquirrelAppendage("character/thief/4_shadow/shadowsoul/ap_shadowsoul.nut");
		if (apd)
		{
			local curApdT = apd.getTimer().Get();
		
			local ski1EncodeT = apd.getVar("CoolTimeSkill").get_vector(0);
			local ski1CoolTime = obj.sq_GetIntData(SKILL_SHADOW_SOUL, 0);
			
			if (curApdT - ski1EncodeT < ski1CoolTime)
				return ;
			
			apd.getVar("CoolTimeSkill").set_vector(0,curApdT);
			
		}
		
		local pIntVec = sq_GetGlobalIntVector();
		sq_IntVectorClear(pIntVec);
		sq_IntVectorPush(pIntVec, 1);			
		obj.addSetStatePacket(STATE_SHADOW_SOUL , pIntVec,  STATE_PRIORITY_USER, false, "");
		return ;
	}
}



function checkCommandEnable_shaowsoul(obj)  
{
	local state = obj.getState();
	if (!CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/thief/4_shadow/shadowsoul/ap_shadowsoul.nut"))
	{
		if (state == 0)
			return true;
	
	}else
	{
		return true;
	}
	
	return false;
}
