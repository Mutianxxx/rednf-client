

function checkCommandEnable_deitiesrebirth(obj)
{
	return true;
}



function checkExecutableSkill_deitiesrebirth(obj)
{
	if(!obj) return false;
	local now_z = obj.getZPos();
	if(now_z>1){
		return false;
	}
	local isUse = obj.sq_IsUseSkill(SKILL_DEITIESREBIRTH);
	if(isUse)
	{
		obj.sq_IntVectClear();
		obj.sq_IntVectPush(0);
		obj.sq_AddSetStatePacket(STATE_DEITIESREBIRTH, STATE_PRIORITY_IGNORE_FORCE, true);
		return true;
	}
	return false;
}



function onSetState_deitiesrebirth(obj, state, datas, isResetTimer)
{	
	if(!obj) return;

	local subState = obj.sq_GetVectorData(datas, 0);
	obj.setSkillSubState(subState);
	obj.sq_StopMove();
	obj.sq_SetStaticSpeedInfo(SPEED_TYPE_CAST_SPEED, SPEED_TYPE_CAST_SPEED,SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);
	switch(subState)
	{
		case 0:
			obj.sq_PlaySound("TF_SIXROTATION_01");
			obj.sq_SetCurrentAnimation(CUSTOM_ANI_FIREHIDE);
			local skill = sq_GetSkill(obj, SKILL_DEITIESREBIRTH);
			local skill_level = sq_GetSkillLevel(obj, SKILL_DEITIESREBIRTH);
			local castTime = sq_GetCastTime(obj, SKILL_DEITIESREBIRTH, skill_level);
			if(sq_GetSkillLevel(obj,123)>0)
			{
				local ldlhsppedRate =  sq_GetLevelData(obj, 123, 4, sq_GetSkillLevel(obj, 123));
				castTime = (castTime*ldlhsppedRate)/100;
			}
			local animation = sq_GetCurrentAnimation(obj);
			local startTime = sq_GetFrameStartTime(animation, 3);
			local speedRate = startTime.tofloat() / castTime.tofloat();
			obj.sq_SetStaticSpeedInfo(SPEED_TYPE_CAST_SPEED, SPEED_TYPE_CAST_SPEED, SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, speedRate, speedRate);
			sq_StartDrawCastGauge(obj, startTime, true);
		break;
	}
}



function onEndCurrentAni_deitiesrebirth(obj)
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



function onEndState_deitiesrebirth(obj, new_state)
{
	if(!obj) return;

	local new_state = obj.getSkillSubState();
	switch(new_state)
	{
		case 0:
			local skill_level = sq_GetSkillLevel(obj, SKILL_DEITIESREBIRTH);
			local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, SKILL_DEITIESREBIRTH, false, "character/thief/3_kunoich/deitiesrebirth/ap_deitiesrebirth.nut", false);
			appendage.setAppendCauseSkill(BUFF_CAUSE_SKILL, sq_getJob(obj), SKILL_DEITIESREBIRTH, skill_level);
			CNSquirrelAppendage.sq_AppendAppendageID(appendage, obj, obj, APID_DEITIESREBIRTH, true);

			appendage = obj.GetSquirrelAppendage("character/thief/3_kunoich/deitiesrebirth/ap_deitiesrebirth.nut");
			if(appendage)
			{
				local change_time = sq_GetIntData(obj, SKILL_DEITIESREBIRTH, 0);
				appendage.sq_SetValidTime(change_time);
				appendage.setBuffIconImage(153);
			}
			
		break;
	}
	sq_EndDrawCastGauge(obj);
}


