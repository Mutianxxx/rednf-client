//////////////////////////////////////////////////////////////////////////////////////////////////
//									
//////////////////////////////////////////////////////////////////////////////////////////////////








function checkCommandEnable_firehide(obj)
{

	return true;
}



function checkExecutableSkill_firehide(obj)
{
	if(!obj) return false;
	local now_z = obj.getZPos();
	if(now_z>1){
		return false;
	}
	local isUse = obj.sq_IsUseSkill(SKILL_FIREHIDE);
	if(isUse)
	{
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(0);
		obj.sq_AddSetStatePacket(STATE_FIREHIDE, STATE_PRIORITY_IGNORE_FORCE, true);
		return true;
	}
	return false;
}



function onSetState_firehide(obj, state, datas, isResetTimer)
{	
	if(!obj) return;

	local subState = obj.sq_GetVectorData(datas, 0);
	obj.setSkillSubState(subState);
	obj.sq_StopMove();
	obj.sq_SetStaticSpeedInfo(SPEED_TYPE_CAST_SPEED, SPEED_TYPE_CAST_SPEED,SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);
	switch(subState)
	{
		case 0:
			obj.sq_SetCurrentAnimation(CUSTOM_ANI_FIREHIDE);
			local skill = sq_GetSkill(obj, SKILL_FIREHIDE);
			local skill_level = sq_GetSkillLevel(obj, SKILL_FIREHIDE);
			local castTime = sq_GetCastTime(obj, SKILL_FIREHIDE, skill_level);
			local animation = sq_GetCurrentAnimation(obj);
			local startTime = sq_GetFrameStartTime(animation, 3);
			local speedRate = startTime.tofloat() / castTime.tofloat();
			obj.sq_SetStaticSpeedInfo(SPEED_TYPE_CAST_SPEED, SPEED_TYPE_CAST_SPEED, SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, speedRate, speedRate);
			sq_StartDrawCastGauge(obj, startTime, true);
			obj.sq_PlaySound("R_TF_FIREHIDE");
		break;
	}
}



function onEndCurrentAni_firehide(obj)
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
		break;
	}
}



function onEndState_firehide(obj, new_state)
{
	if(!obj) return;

	local new_state = obj.getSkillSubState();
	switch(new_state)
	{
		case 0:
			if (CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/thief/3_kunoich/firehide/ap_firehide.nut"))
			{
				CNSquirrelAppendage.sq_RemoveAppendage(obj, "character/thief/3_kunoich/firehide/ap_firehide.nut");
			}
			local skill = sq_GetSkill(obj, SKILL_FIREHIDE);
			local skill_level = sq_GetSkillLevel(obj, SKILL_FIREHIDE);
			local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, SKILL_FIREHIDE, false, "character/thief/3_kunoich/firehide/ap_firehide.nut", false);
			appendage.setAppendCauseSkill(BUFF_CAUSE_SKILL, sq_getJob(obj), SKILL_FIREHIDE, skill_level);
			CNSquirrelAppendage.sq_AppendAppendageID(appendage, obj, obj, APID_FIREHIDE, true);
			local value0 = sq_GetLevelData(obj, SKILL_FIREHIDE, 1, skill_level).tofloat();
			local value1 = sq_GetLevelData(obj, SKILL_FIREHIDE, 2, skill_level).tofloat();
			appendage = obj.GetSquirrelAppendage("character/thief/3_kunoich/firehide/ap_firehide.nut");
		
			if(appendage)
			{
				local change_time = sq_GetIntData(obj, SKILL_FIREHIDE, 0);
				appendage.sq_SetValidTime(change_time);
				appendage.setBuffIconImage(72);
			}
			
			local change_appendage = appendage.sq_getChangeStatus("firehide");
			if(!change_appendage)
			{
				change_appendage = appendage.sq_AddChangeStatus("firehide",obj, obj, 0, 0, true, 0);
			}
			if (change_appendage){
				change_appendage.clearParameter();
				change_appendage.addParameter(CHANGE_STATUS_TYPE_EQUIPMENT_PHYSICAL_DEFENSE, true, value0 );
				change_appendage.addParameter(CHANGE_STATUS_TYPE_EQUIPMENT_MAGICAL_DEFENSE, true, value1 );
			}
			
		break;
	}
	sq_EndDrawCastGauge(obj);
}


