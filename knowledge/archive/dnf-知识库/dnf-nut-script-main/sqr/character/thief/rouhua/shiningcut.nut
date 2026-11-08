


function checkExecutableSkill_ShiningCut(obj)  
{
	if (!obj) return false;

	local isUseSkill = obj.sq_IsUseSkill(3);
	if (isUseSkill) {

        obj.sq_IntVectClear();
        obj.sq_IntVectPush(3);
        obj.sq_IntVectPush(0);
        obj.sq_IntVectPush(0);
		obj.sq_AddSetStatePacket(22, STATE_PRIORITY_USER, true);
		return true;
	}
	return false;
}

function checkCommandEnable_ShiningCut(obj)
{

	return true;
}
