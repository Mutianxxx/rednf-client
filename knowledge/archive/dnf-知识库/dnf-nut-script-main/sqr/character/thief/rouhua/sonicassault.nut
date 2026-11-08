
//57    0


function checkExecutableSkill_SonicAssault(obj)  
{
	if (!obj) return false;

	local isUseSkill = obj.sq_IsUseSkill(34);
	if (isUseSkill) {

        obj.sq_IntVectClear();
        obj.sq_IntVectPush(0);
        obj.sq_IntVectPush(0);
        obj.sq_IntVectPush(0);
		obj.sq_AddSetStatePacket(57, STATE_PRIORITY_USER, true);
		return true;
	}
	return false;
}

function checkCommandEnable_SonicAssault(obj)
{

	return true;
}
