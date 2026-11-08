
//37   32


function checkExecutableSkill_LightningArrow(obj)  
{
	if (!obj) return false;

	local isUseSkill = obj.sq_IsUseSkill(45);
	if (isUseSkill) {

        obj.sq_IntVectClear();
        obj.sq_IntVectPush(32);
		obj.sq_AddSetStatePacket(37, STATE_PRIORITY_USER, true);
		return true;
	}
	return false;
}

function checkCommandEnable_LightningArrow(obj)
{

	return true;
}
