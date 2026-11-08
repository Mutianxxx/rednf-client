

function checkExecutableSkill_Sway(obj)  
{
	if (!obj) return false;

	local isUseSkill = obj.sq_IsUseSkill(3);
	if (isUseSkill) {

        obj.sq_IntVectClear();
        obj.sq_IntVectPush(0);
        obj.sq_IntVectPush(0);
		obj.sq_AddSetStatePacket(22, STATE_PRIORITY_USER, true);
		return true;
	}
	return false;
}

function checkCommandEnable_Sway(obj)
{

	return true;
}

function onSetState_Sway(obj, state, datas, isResetTimer)
{

    if (CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/new_priest/lanquan/sway/ap_sway.nut"))
    {

        CNSquirrelAppendage.sq_RemoveAppendage(obj, "character/new_priest/lanquan/sway/ap_sway.nut");
    }

	local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, 3, true,
	 "character/new_priest/lanquan/sway/ap_sway.nut", false);
	//sq_AddMessage(4);
    appendage.sq_SetValidTime(2000);
	local skill_level = sq_GetSkillLevel(obj, 3);
	appendage.setAppendCauseSkill(BUFF_CAUSE_SKILL, sq_getJob(obj), 3, skill_level);	
	CNSquirrelAppendage.sq_AppendAppendageID(appendage, obj, obj, 3, true);


    return true;
}