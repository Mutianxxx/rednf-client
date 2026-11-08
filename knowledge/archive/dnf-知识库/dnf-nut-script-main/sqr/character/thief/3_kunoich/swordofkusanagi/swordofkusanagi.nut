//////////////////////////////////////////////////////////////////////////////////////////////////
//									
//////////////////////////////////////////////////////////////////////////////////////////////////








function checkCommandEnable_swordofkusanagi(obj)
{
	local now_z = obj.getZPos();
	if(now_z>1){
		return false;
	}
	return true;
}



function checkExecutableSkill_swordofkusanagi(obj)
{
	if(!obj) return false;
	local now_z = obj.getZPos();
	if(now_z>1){
		return false;
	}
	local isUse = obj.sq_IsUseSkill(SKILL_SWORDOFKUSANAGI);
	if(isUse)
	{
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(0);
		obj.sq_AddSetStatePacket(STATE_SWORDOFKUSANAGI, STATE_PRIORITY_IGNORE_FORCE, true);
		return true;
	}
	return false;
}



function onSetState_swordofkusanagi(obj, state, datas, isResetTimer)
{	
	if(!obj) return;

	local subState = obj.sq_GetVectorData(datas, 0);
	obj.setSkillSubState(subState);
	obj.sq_StopMove();

	switch(subState)
	{
		case 0:
			obj.sq_SetCurrentAnimation(CUSTOM_ANI_SWORDOFKUSANAGI);
		break;
	}
}



function onEndCurrentAni_swordofkusanagi(obj)
{
	if(!obj) return;

	if(!obj.isMyControlObject())
	{
		return;
	}

	local subState = obj.getSkillSubState();
	switch(subState)
	{
		case 0:
			obj.sq_IntVectClear();
			obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_IGNORE_FORCE, true);
			local skill_level = sq_GetSkillLevel(obj, SKILL_SWORDOFKUSANAGI);
			local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, SKILL_SWORDOFKUSANAGI, false, "character/thief/3_kunoich/swordofkusanagi/ap_swordofkusanagi.nut", false);
			appendage.setAppendCauseSkill(BUFF_CAUSE_SKILL, sq_getJob(obj), SKILL_SWORDOFKUSANAGI, skill_level);
			CNSquirrelAppendage.sq_AppendAppendageID(appendage, obj, obj, APID_SWORDOFKUSANAGI, true);

			appendage = obj.GetSquirrelAppendage("character/thief/3_kunoich/swordofkusanagi/ap_swordofkusanagi.nut");
			if(appendage)
			{
				local change_time = sq_GetIntData(obj, SKILL_SWORDOFKUSANAGI, 0);
				appendage.sq_SetValidTime(change_time);
				appendage.setBuffIconImage(90);
			}
		break;
	}
}



function onKeyFrameFlag_swordofkusanagi(obj, flagIndex)
{
	if(!obj) return false;

	local subState = obj.getSkillSubState();
	switch(subState)
	{
		case 0:
			switch(flagIndex)
			{
				case 10001:
					if(obj.isMyControlObject())
					{
						//create_cutin(obj, 34, "etc/ultimateskillani/2ndcutin/thief/kunoich.ani");
					}
				break;
			}
		break;
	}
	return true;
}

