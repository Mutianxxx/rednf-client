
//34  26


function checkExecutableSkill_ChainSaw(obj)  
{
	if (!obj) return false;

	local isUseSkill = obj.sq_IsUseSkill(41);
	if (isUseSkill) {

        obj.sq_IntVectClear();
        obj.sq_IntVectPush(26);
        obj.sq_IntVectPush(0);
        obj.sq_IntVectPush(0);
		obj.sq_AddSetStatePacket(34, STATE_PRIORITY_USER, true);
		return true;
	}
	return false;
}

function checkCommandEnable_ChainSaw(obj)
{

	return true;
}
