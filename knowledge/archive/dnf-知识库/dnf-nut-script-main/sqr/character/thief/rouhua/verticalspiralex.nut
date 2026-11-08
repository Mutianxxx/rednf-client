
//65    1



function checkExecutableSkill_VerticalSpiralEx(obj)  
{
	if (!obj) return false;

	local isUseSkill = obj.sq_IsUseSkill(75);
	if (isUseSkill) {

        obj.sq_IntVectClear();
        obj.sq_IntVectPush(1);
        obj.sq_IntVectPush(0);
        obj.sq_IntVectPush(0);
		obj.sq_AddSetStatePacket(65, STATE_PRIORITY_USER, true);
		return true;
	}
	return false;
}

function checkCommandEnable_VerticalSpiralEx(obj)
{

	return true;
}
