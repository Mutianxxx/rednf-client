//CUSTOM_ANI_DELUSION_CASTING <- 335
//CUSTOM_ANI_DELUSION_BODY <- 336

function checkExecutableSkill_delusion(obj)  
{
	if (!obj) return false;
	local isUse = obj.sq_IsUseSkill(SKILL_DELUSION);

	if (isUse) {
		obj.getVar("state").clear_vector();
        obj.getVar("state").push_vector(0);
		obj.sq_AddSetStatePacket(STATE_DELUSION , STATE_PRIORITY_USER, false);
		return true;
	}

	return false;
}


function checkCommandEnable_delusion(obj)
{
	if (!obj) return false;
	return true;

}
//DELUSION


function onSetState_DELUSION(obj, state, datas, isResetTimer)
{
	obj.sq_StopMove();
	local state = obj.getVar("state").get_vector(0);
	//obj.setSkillSubState(state);
    if (state == 0)
    {
        obj.sq_SetCurrentAnimation(CUSTOM_ANI_DELUSION_CASTING );
		local castTime = sq_GetCastTime(obj, SKILL_DELUSION, sq_GetSkillLevel(obj, SKILL_DELUSION)  );
		local animation = sq_GetCurrentAnimation(obj);
		local startTime = animation.getDelaySum(false);
		local speedRate = startTime.tofloat() / castTime.tofloat();
		obj.sq_SetStaticSpeedInfo(SPEED_TYPE_CAST_SPEED, SPEED_TYPE_CAST_SPEED,
			SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, speedRate, speedRate);

		sq_StartDrawCastGauge(obj, castTime, true);

    }else if (state == 1)
    {
        obj.sq_SetCurrentAnimation(CUSTOM_ANI_DELUSION_BODY);
        if(!obj.isMyControlObject()) {
            return;
        }

        if (CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/atmage/delusion/ap_delusion.nut"))
        {

            CNSquirrelAppendage.sq_RemoveAppendage(obj, "character/atmage/delusion/ap_delusion.nut");
        }

		local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, SKILL_DELUSION, true,
		 "character/atmage/delusion/ap_delusion.nut", false);
        //pvp ?Y???????
        if (sq_isPVPMode())
        {
            local change_time = obj.sq_GetIntData(SKILL_DELUSION, 0);
            appendage.sq_SetValidTime(change_time);
        }

		local skill_level = sq_GetSkillLevel(obj, SKILL_DELUSION);
		appendage.setAppendCauseSkill(BUFF_CAUSE_SKILL, sq_getJob(obj), SKILL_DELUSION, skill_level);
		
		CNSquirrelAppendage.sq_AppendAppendageID(appendage, obj, obj, SKILL_DELUSION, true);
		appendage.setBuffIconImage(108);

    }
}


function onEndCurrentAni_DELUSION(obj)
{
	if(!obj.isMyControlObject()) {
		return;
	}
    local state = obj.getVar("state").get_vector(0);
    if (state == 0)
    {

		obj.getVar("state").clear_vector();
        obj.getVar("state").push_vector(1);
		obj.sq_AddSetStatePacket(STATE_DELUSION , STATE_PRIORITY_USER, false);
    }else if (state == 1){

		obj.sq_AddSetStatePacket(STATE_STAND , STATE_PRIORITY_USER, true);
    }
}