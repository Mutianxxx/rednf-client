


function checkExecutableSkill_Congest(obj)
{
	if (!obj) return false;
	local useskill = obj.sq_IsUseSkill(76);
	if (useskill)
	{
		
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(0);
		obj.sq_AddSetStatePacket(102, STATE_PRIORITY_IGNORE_FORCE, true);
		local ap = "character/atswordman/4_darktempler/congest/ap_congest.nut";
		local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, -1, false, ap, false);
		appendage.sq_SetValidTime(obj.sq_GetLevelData(76, 1, sq_GetSkillLevel(obj, 76)));
		appendage.setAppendCauseSkill(BUFF_CAUSE_SKILL, sq_getJob(obj), 76, sq_GetSkillLevel(obj, 76));
		appendage.setEnableIsBuff(true);
		CNSquirrelAppendage.sq_Append(appendage, obj, obj, true);
		return true;
	}
	return false;
}

function checkCommandEnable_Congest(obj)
{
	if (!obj) return false
	return true
}

function onSetState_Congest(obj, CQWBeSnrfA2cmJErcGa, data, CQfpskA53c94q5otEoVv)
{	
	if(!obj) return;
	local substate = obj.sq_GetVectorData(data, 0)
	obj.setSkillSubState(substate)
	switch(substate)
	{
		case 0:
			obj.sq_StopMove();
			obj.sq_SetCurrentAnimation(472);
			break;
	}
	//obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED,SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0)
}

function onEndCurrentAni_Congest(obj)
{
	if(!obj) return;
	local CQndkB1jkwHGbHuO = obj.getSkillSubState();
	switch(CQndkB1jkwHGbHuO)
	{
		case 0:
			obj.sq_IntVectClear();
			obj.sq_AddSetStatePacket(0, STATE_PRIORITY_IGNORE_FORCE, true);
			break;
	}
}
