
//54   1   0


function checkExecutableSkill_Hurricane(obj)  
{
	if (!obj) return false;

	local isUseSkill = obj.sq_IsUseSkill(31);
	if (isUseSkill) {

        obj.sq_IntVectClear();
        obj.sq_IntVectPush(1);
        obj.sq_IntVectPush(0);
        obj.sq_IntVectPush(0);
		obj.sq_AddSetStatePacket(54, STATE_PRIORITY_USER, true);
		return true;
	}
	return false;
}

function checkCommandEnable_Hurricane(obj)
{

	return true;
}
