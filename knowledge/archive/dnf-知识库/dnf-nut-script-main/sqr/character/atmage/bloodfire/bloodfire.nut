//CUSTOM_ANI_BLOOD_BURN_READY <- 341
//CUSTOM_ANI_BLOOD_BURN_START <- 342

function checkExecutableSkill_bloodfire(obj)  
{
	if (!obj) return false;

	local isUseSkill = obj.sq_IsUseSkill(SKILL_BLOODFIRE);
	if (isUseSkill) {

		obj.sq_IntVectClear();
		obj.sq_IntVectPush(0);	// subState????
		obj.sq_AddSetStatePacket(STATE_BLOODFIRE, STATE_PRIORITY_USER, true);
		return true;
	}
	return false;
}

function checkCommandEnable_bloodfire(obj)
{
        return true;
}

function onSetState_BLOODFIRE(obj, state, datas, isResetTimer)
{
	obj.sq_StopMove();
	local subState = obj.sq_GetVectorData(datas, 0);
	obj.setSkillSubState(subState);
    if (subState == 0)
    {
		//createNewAwakeBuffEffectWithAniPath(obj,95,"etc/ultimateskillani/buff/atmage_bloodmage_neo_buff.ani");
        obj.sq_SetCurrentAnimation(CUSTOM_ANI_BLOOD_BURN_READY);

		local castTime = sq_GetCastTime(obj, SKILL_BLOODFIRE, sq_GetSkillLevel(obj, SKILL_BLOODFIRE)  );
		sq_StartDrawCastGauge(obj, castTime, true);

    }else if (subState == 1)
    {
        obj.sq_SetShake(obj, 1, 100);
        obj.sq_SetCurrentAnimation(CUSTOM_ANI_BLOOD_BURN_START);

        if(obj.isMyControlObject())
        {
            if (CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/atmage/bloodfire/ap_bloodfire.nut"))
            {

                CNSquirrelAppendage.sq_RemoveAppendage(obj, "character/atmage/bloodfire/ap_bloodfire.nut");
            }

            local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, SKILL_BLOODFIRE, true,
             "character/atmage/bloodfire/ap_bloodfire.nut", false);

            local skill_level = sq_GetSkillLevel(obj, SKILL_BLOODFIRE);

            appendage.setAppendCauseSkill(BUFF_CAUSE_SKILL, sq_getJob(obj), SKILL_BLOODFIRE, skill_level);

            CNSquirrelAppendage.sq_AppendAppendageID(appendage, obj, obj, APID_SKILL_ELEMENTAL_CHANGE, false);
            appendage.setEnableIsBuff(true);
            appendage.setBuffIconImage(109);
            obj.sq_PlaySound("BLOODBURN_CAST");
            if (sq_isPVPMode())
            {
                local change_time = obj.sq_GetIntData(SKILL_BLOODFIRE, 0);
                appendage.sq_SetValidTime(change_time);
            }
        }
    }   
}

function onProc_BLOODFIRE(obj)
{
	if(!obj.isMyControlObject()) {
		return;
	}
	local subState = obj.getSkillSubState();
    if (subState == 0)
    {
        local pAni = obj.sq_GetCurrentAni();
        local frmIndex = obj.sq_GetCurrentFrameIndex(pAni);
        local currentT = sq_GetCurrentTime(pAni);
        if (currentT > 200)
        {
            obj.sq_IntVectClear();
            obj.sq_IntVectPush(1);	// subState????
            obj.sq_AddSetStatePacket(STATE_BLOODFIRE, STATE_PRIORITY_USER, true);
        }
    }
}

function onEndCurrentAni_BLOODFIRE(obj)
{

	if (!obj)
		return;
	if(!obj.isMyControlObject()) {
		return;
	}

	local subState = obj.getSkillSubState();
    if (subState == 0)
    {

    }else if (subState == 1){
        obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
    }
}