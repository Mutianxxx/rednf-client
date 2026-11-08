function checkExecutableSkill_assassinofcreed(obj)  
{
	if (!obj) return false;

	local isUseSkill = obj.sq_IsUseSkill(SKILL_ASSASSINOFCREED);
	if (isUseSkill) 
    {

		obj.sq_AddSetStatePacket(STATE_ASSASSINOFCREED, STATE_PRIORITY_USER, true);
		return true;
	}
	return false;
}


function checkCommandEnable_assassinofcreed(obj)  
{

	if(!obj)
		return false;
	local state = obj.sq_GetState();
		
    if (state == STATE_STAND)
    {
        return true;
    }
    if (state == STATE_DASH)
    {
        return true;
    }
		
	return false;
}



function onSetState_ASSASSINOFCREED(obj, state, datas, isResetTimer)
{	
    obj.sq_StopMove();
        obj.sq_SetCurrentAnimation(CUSTOM_ANI_ASSASSINOFCREED_BODY );
        obj.getVar("flag").clear_vector();
        obj.getVar("flag").push_vector(0);

        local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, SKILL_ASSASSINOFCREED, false,
        "character/thief/4_shadow/assassinofcreed/ap_assassinofcreed.nut", false);

        local skill_level = sq_GetSkillLevel(obj, SKILL_ASSASSINOFCREED);
        appendage.setAppendCauseSkill(BUFF_CAUSE_SKILL, sq_getJob(obj), SKILL_ASSASSINOFCREED, skill_level);
        CNSquirrelAppendage.sq_AppendAppendageID(appendage, obj, obj, SKILL_ASSASSINOFCREED, true);
	appendage.setBuffIconImage(87);
		local value0 = sq_GetLevelData(obj, SKILL_ASSASSINOFCREED, 1, skill_level ); 


		local change_appendage = appendage.sq_getChangeStatus("assassinofcreed");

		if(!change_appendage)
        {
			change_appendage = appendage.sq_AddChangeStatusAppendageID(obj, obj, 0, 
			CHANGE_STATUS_TYPE_PHYSICAL_CRITICAL_HIT_RATE, 
			false, value0, APID_COMMON);

		}
        if (change_appendage)
        {
			change_appendage.clearParameter();
            change_appendage.addParameter(CHANGE_STATUS_TYPE_PHYSICAL_CRITICAL_HIT_RATE, false, value0.tofloat());
        }
}

function onEndCurrentAni_ASSASSINOFCREED(obj)
{

    obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
}