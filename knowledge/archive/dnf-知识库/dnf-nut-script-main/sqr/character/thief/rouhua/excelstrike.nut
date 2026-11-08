
//38   40    0

//38    40    1

//38   127


function checkExecutableSkill_ExcelStrike(obj)  
{
	if (!obj) return false;

	local isUseSkill = obj.sq_IsUseSkill(47);
	if (isUseSkill) {

        obj.sq_IntVectClear();
        obj.sq_IntVectPush(40);
        obj.sq_IntVectPush(0);
		obj.sq_AddSetStatePacket(38, STATE_PRIORITY_USER, true);
		return true;
	}
	return false;
}

function checkCommandEnable_ExcelStrike(obj)
{

	return true;
}
