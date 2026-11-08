
//52  0


function checkExecutableSkill_DoublePierce(obj)  
{
	if (!obj) return false;

	local isUseSkill = obj.sq_IsUseSkill(27);
	if (isUseSkill) {

        obj.sq_IntVectClear();
        obj.sq_IntVectPush(0);
		obj.sq_AddSetStatePacket(52, STATE_PRIORITY_USER, true);
		return true;
	}
	return false;
}

function checkCommandEnable_DoublePierce(obj)
{

	return true;
}
