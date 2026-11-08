function checkExecutableSkill_darkshadow_new(obj)  
{
	if (!obj) return false;

	local isUseSkill = obj.sq_IsUseSkill(SKILL_DARKSHADOW_NEW);
	if (isUseSkill) 
    {

        obj.getVar("state").clear_vector();
        obj.getVar("state").push_vector(0);
		obj.sq_AddSetStatePacket(STATE_DARKSHADOW_NEW, STATE_PRIORITY_USER, true);
		return true;
	}
	return false;
}


function checkCommandEnable_darkshadow_new(obj)
{

	return true;
}

function sendDarkShadow_NEW(obj)
{


    if (obj.getVar("flag").get_vector(0) == 1)
        return false;

    obj.getVar("flag").clear_vector();
    obj.getVar("flag").push_vector(1);

    local attackBonusRate = obj.sq_GetBonusRateWithPassive(SKILL_DARKSHADOW_NEW, STATE_DARKSHADOW_NEW, 1, 1.0);
    local size = sq_GetLevelData(obj, SKILL_DARKSHADOW_NEW, 2, sq_GetSkillLevel(obj, SKILL_DARKSHADOW_NEW) );

       local waitTime = obj.sq_GetIntData(SKILL_DARKSHADOW, 0);
       local attackTime = waitTime / sq_GetLevelData(obj, SKILL_DARKSHADOW_NEW, 0, sq_GetSkillLevel(obj, SKILL_DARKSHADOW_NEW) );

            obj.sq_StartWrite();
            obj.sq_WriteDword(attackBonusRate);
            obj.sq_WriteDword(1);
            obj.sq_WriteDword(waitTime);
            obj.sq_WriteDword(attackTime);
            obj.sq_SendCreatePassiveObjectPacket(24330, 0, 120, 1, 0);

}


function onSetState_DARKSHADOW_NEW(obj, state, datas, isResetTimer)
{

	obj.sq_StopMove();
    local state = obj.getVar("state").get_vector(0);

    if (state == 0)
    {


		local skillLevel = sq_GetSkillLevel(obj, SKILL_DARKSHADOW_NEW);
		local castTime  = sq_GetCastTime(obj, SKILL_DARKSHADOW_NEW, skillLevel);

        obj.getVar("cast").clear_vector();
        obj.getVar("cast").push_vector(castTime);

		sq_StartDrawCastGauge(obj, castTime, true);


        obj.sq_SetCurrentAnimation(CUSTOM_ANI_DARKSHADOW_CASTING_BOBY);


    }

    if (state == 1)
    {

        obj.getVar("flag").clear_vector();
        obj.getVar("flag").push_vector(0);

        obj.sq_SetCurrentAnimation(CUSTOM_ANI_DARKSHADOW_OUT_BOBY);
    }

}

function onProc_DARKSHADOW_NEW(obj)
{

    local state = obj.getVar("state").get_vector(0);

    if (state == 0)
    {

        local pAni = obj.sq_GetCurrentAni();
        local currentT = sq_GetCurrentTime(pAni);

        if (currentT > obj.getVar("cast").get_vector(0) )
        {

            obj.getVar("state").clear_vector();
            obj.getVar("state").push_vector(1);
            obj.sq_AddSetStatePacket(STATE_DARKSHADOW_NEW, STATE_PRIORITY_USER, true);
        }
    }
    
}

function onEndCurrentAni_DARKSHADOW_NEW(obj)
{
    local state = obj.getVar("state").get_vector(0);

    if (state == 1)
    {

        obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
    }

}

function onKeyFrameFlag_DARKSHADOW_NEW(obj,flagIndex)
{

    local state = obj.getVar("state").get_vector(0);

    if (state == 1)
    {

        if (flagIndex == 1)
        {

            sendDarkShadow_NEW(obj);
        }


    }

}






