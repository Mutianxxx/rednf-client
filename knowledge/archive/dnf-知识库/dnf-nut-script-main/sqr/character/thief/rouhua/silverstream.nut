
//45   92


function checkExecutableSkill_SilverStream(obj)  
{
	if (!obj) return false;

	local isUseSkill = obj.sq_IsUseSkill(57);
	if (isUseSkill) {

        obj.sq_IntVectClear();
        obj.sq_IntVectPush(92);
        obj.sq_IntVectPush(0);
        obj.sq_IntVectPush(0);
		obj.sq_AddSetStatePacket(45, STATE_PRIORITY_USER, true);
		return true;
	}
	return false;
}

function checkCommandEnable_SilverStream(obj)
{

	return true;
}
