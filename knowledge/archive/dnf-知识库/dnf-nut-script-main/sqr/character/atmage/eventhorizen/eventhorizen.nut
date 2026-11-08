function checkExecutableSkill_eventhorizen(obj)
{

	if(!obj) return false;


	if (!obj.isMyControlObject() )
		return false;

	if (isEventHorizen(obj))
	{
		return false;

	}
	if ( getBreakSenseEnegry(obj) < obj.sq_GetIntData(SKILL_EVENTHORIZEN, 0) * 100 )
	{
		return false;
	}

	if(!obj.isMyControlObject()) {
		return;
	}

	local b_useskill = obj.sq_IsUseSkill(SKILL_EVENTHORIZEN);
	if(b_useskill)
	{
		local skill_level = sq_GetSkillLevel(obj, SKILL_FATE_0);
		local noRate = sq_GetLevelData(obj, SKILL_FATE_0, 8, skill_level);

		if (noRate < sq_getRandom(0, 1000) )
			setBreakSenseEnegry( obj,getBreakSenseEnegry(obj) - obj.sq_GetIntData(SKILL_EVENTHORIZEN, 0) * 100 );

		local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, SKILL_EVENTHORIZEN, true,"character/atmage/eventhorizen/ap_eventhorizen.nut", false);


		local skill_level = sq_GetSkillLevel(obj, SKILL_EVENTHORIZEN);
		appendage.setAppendCauseSkill(BUFF_CAUSE_SKILL, sq_getJob(obj), SKILL_EVENTHORIZEN, skill_level);
		
		CNSquirrelAppendage.sq_AppendAppendageID(appendage, obj, obj, SKILL_EVENTHORIZEN, true);
		
		appendage.setBuffIconImage(107);

		obj.sq_PlaySound("MW_EVENT_HORIZEN"); 

		return true;
	}	
	
	return false;

}

function checkCommandEnable_eventhorizen(obj)
{

	if(!obj) return false;

	if (isEventHorizen(obj))
	{
		return false;

	}

	return true;
}