function checkExecutableSkill_Skillb03(obj)
{
	if (!obj) return false;
	local isUse = obj.sq_IsUseSkill(SKILL_AtSwordManB03);
	
	if (isUse)
	{
		obj.sq_AddSetStatePacket(STATE_AtSwordManB03 , STATE_PRIORITY_USER, false);
		return true;
	}
	
	return false;
}

function checkCommandEnable_Skillb03(obj)
{
	if (!obj) return false;
	local state = obj.sq_GetState();
	
	if (state == STATE_STAND)
	
		return true;

		return true;

}

function onSetState_Skillb03(obj, state, datas, isResetTimer)
{	
	if(!obj) return;
	
		obj.sq_StopMove();
		obj.sq_SetCurrentAnimation(ANI_Frenzy);

}


function onKeyFrameFlag_Skillb03(obj,flagIndex)
{
	if(!obj)
		return false;
		if (flagIndex == 1)
		{
			local skill_level = sq_GetSkillLevel(obj, SKILL_AtSwordManB03);

			local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, SKILL_AtSwordManB03, false,
			 "character/atswordman/atswordman2/atswordman03/ap_atswordmanb03.nut", false);

			appendage.setAppendCauseSkill(BUFF_CAUSE_SKILL, sq_getJob(obj), SKILL_AtSwordManB03, skill_level);
		
			CNSquirrelAppendage.sq_AppendAppendageID(appendage, obj, obj, STATE_AtSwordManB03, true);
		
			appendage = obj.GetSquirrelAppendage("character/atswordman/atswordman2/atswordman03/ap_atswordmanb03.nut");
			if(appendage)
			{

					local change_appendage = appendage.sq_getChangeStatus("atswordb03");
					if(!change_appendage)
					{
						change_appendage = appendage.sq_AddChangeStatusAppendageID(obj, obj, 0, 
						CHANGE_STATUS_TYPE_ATTACK_SPEED, 
						false, 0, APID_COMMON);
						change_appendage = appendage.sq_AddChangeStatusAppendageID(obj, obj, 0, 
						CHANGE_STATUS_TYPE_MOVE_SPEED, 
						false, 0, APID_COMMON);
					}
					if(change_appendage)
					{
						local AtkSpeed = obj.sq_GetLevelData(SKILL_AtSwordManB03, 0, skill_level);

						local MoveSpeed = obj.sq_GetLevelData(SKILL_AtSwordManB03, 1, skill_level);

						print(" AtkSpeed=" + AtkSpeed);
						print(" MoveSpeed=" + MoveSpeed);

						change_appendage.clearParameter();
						change_appendage.addParameter(CHANGE_STATUS_TYPE_ATTACK_SPEED, false, AtkSpeed.tofloat());
						change_appendage.addParameter(CHANGE_STATUS_TYPE_MOVE_SPEED, false, MoveSpeed.tofloat());
					}
			}

		}

	return true;
}



function onEndCurrentAni_Skillb03(obj)
{

	obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
}
