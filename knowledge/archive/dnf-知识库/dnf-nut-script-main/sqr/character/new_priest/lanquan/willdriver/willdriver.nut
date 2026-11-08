
function checkExecutableSkill_WillDriver(obj)  
{
	if (!obj) return false;

	local isUseSkill = obj.sq_IsUseSkill(13);
	if (isUseSkill) {

        obj.sq_IntVectClear();
        obj.sq_IntVectPush(0);
        obj.sq_IntVectPush(0);
		obj.sq_AddSetStatePacket(27, STATE_PRIORITY_USER, true);
		return true;
	}

	return false;
}

function checkCommandEnable_WillDriver(obj)
{

	return true;
}


function onSetState_WillDriver(obj, state, datas, isResetTimer)
{
	if(!obj) return;
        if(obj.isMyControlObject())
	{
		if (CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/new_priest/lanquan/willdriver/ap_willdriver.nut"))
		{
			CNSquirrelAppendage.sq_RemoveAppendage(obj, "character/new_priest/lanquan/willdriver/ap_willdriver.nut");
		}
		
		local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, 13, false, "character/new_priest/lanquan/willdriver/ap_willdriver.nut", true);
		local skill_level = sq_GetSkillLevel(obj, 13);
		appendage.setAppendCauseSkill(BUFF_CAUSE_SKILL, sq_getJob(obj), 13, skill_level);	
		CNSquirrelAppendage.sq_AppendAppendageID(appendage, obj, obj, 13, true);
            
	}

}