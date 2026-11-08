
//56   0

//56   1   0

//zhixian  56   1     1


function checkExecutableSkill_VerticalSpiral(obj)  
{
	if (!obj) return false;

	local isUseSkill = obj.sq_IsUseSkill(33);
	if (isUseSkill) {

        obj.sq_IntVectClear();
        obj.sq_IntVectPush(1);
        obj.sq_IntVectPush(0);
        obj.sq_IntVectPush(0);
		obj.sq_AddSetStatePacket(56, STATE_PRIORITY_USER, true);
		return true;
	}
	return false;
}

function checkCommandEnable_VerticalSpiral(obj)
{

	return true;
}
