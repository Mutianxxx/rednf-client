
//66   116

function checkExecutableSkill_ChainSawEx(obj)  
{
	if (!obj) return false;

	local isUseSkill = obj.sq_IsUseSkill(76);
	if (isUseSkill) {

        obj.sq_IntVectClear();
        obj.sq_IntVectPush(116);
        obj.sq_IntVectPush(0);
        obj.sq_IntVectPush(0);
		obj.sq_AddSetStatePacket(66, STATE_PRIORITY_USER, true);
		return true;
	}
	return false;
}

function checkCommandEnable_ChainSawEx(obj)
{

	return true;
}
