function checkExecutableSkill_elementquake(obj)  
{
	if (!obj) return false;

	local isUseSkill = obj.sq_IsUseSkill(SKILL_ELEMENTQUAKE);
	if (isUseSkill) 
    {
        obj.getVar("state").clear_vector();
        obj.getVar("state").push_vector(0);
		obj.sq_IsEnterSkillLastKeyUnits(SKILL_ELEMENTQUAKE);
		obj.sq_AddSetStatePacket(STATE_ELEMENTQUAKE, STATE_PRIORITY_USER, true);
		return true;
	}
	return false;
}


function checkCommandEnable_elementquake(obj)
{

	return true;
}

function onSetState_ELEMENTQUAKE(obj, state, datas, isResetTimer)
{
	obj.sq_StopMove();

    local state = obj.getVar("state").get_vector(0);


    if (state == 3)
    {

        obj.sq_SetCurrentAnimation(CUSTOM_ANI_ELEMENTQUAKE_BOBY3);
    }
    
    if (state == 2)
    {

        obj.sq_SetCurrentAnimation(CUSTOM_ANI_ELEMENTQUAKE_BOBY2);
    }

    if (state == 1)
    {

        obj.sq_SetCurrentAnimation(CUSTOM_ANI_ELEMENTQUAKE_BOBY1);
    }

    if (state == 0)
    {

		local skillLevel = sq_GetSkillLevel(obj, SKILL_ELEMENTQUAKE);
		local castTime  = sq_GetCastTime(obj, SKILL_ELEMENTQUAKE, skillLevel);

        obj.getVar("isCasting").clear_vector();
        obj.getVar("isCasting").push_vector(0);
        obj.getVar("cast").clear_vector();
        obj.getVar("cast").push_vector(castTime);

		sq_StartDrawCastGauge(obj, castTime, true);

        obj.sq_SetCurrentAnimation(CUSTOM_ANI_ELEMENTQUAKE_BOBY0);
    }

}

function onProc_ELEMENTQUAKE(obj)
{
    local state = obj.getVar("state").get_vector(0);
    local pAni = obj.sq_GetCurrentAni();
    local currentT = sq_GetCurrentTime(pAni);

    if (state == 0)
    {
        if (currentT > obj.getVar("cast").get_vector(0))
        {


            if(obj.isDownSkillLastKey())
            {

                pass;
            }else{

                obj.getVar("isCasting").clear_vector();
                obj.getVar("isCasting").push_vector(1);
            }

        }

        if (obj.getVar("isCasting").get_vector(0) == 1)
        {

            obj.getVar("state").clear_vector();
            obj.getVar("state").push_vector(1);
            obj.sq_AddSetStatePacket(STATE_ELEMENTQUAKE, STATE_PRIORITY_USER, true);

        }
    }

}

function onEndCurrentAni_ELEMENTQUAKE(obj)
{
    local state = obj.getVar("state").get_vector(0);
    if (state == 0)
    {

        pass;

    }
    if (state == 1)
    {
        local attackBonusRate = obj.sq_GetBonusRateWithPassive(SKILL_ELEMENTQUAKE, STATE_ELEMENTQUAKE, 0, 1.0);
        local attackBonusRate2 = obj.sq_GetBonusRateWithPassive(SKILL_ELEMENTQUAKE, STATE_ELEMENTQUAKE, 1, 1.0);
        local attackBonusRate3 = obj.sq_GetBonusRateWithPassive(SKILL_ELEMENTQUAKE, STATE_ELEMENTQUAKE, 2, 1.0);
        local attackBonusRate4 = obj.sq_GetBonusRateWithPassive(SKILL_ELEMENTQUAKE, STATE_ELEMENTQUAKE, 3, 1.0);


        obj.sq_StartWrite();
        obj.sq_WriteDword(attackBonusRate);
        obj.sq_WriteDword(attackBonusRate2);
        obj.sq_WriteDword(attackBonusRate3);
        obj.sq_WriteDword(attackBonusRate4);

        obj.sq_SendCreatePassiveObjectPacket(24329, 0, 350, 1, 0);



        obj.getVar("state").clear_vector();
        obj.getVar("state").push_vector(2);
        obj.sq_AddSetStatePacket(STATE_ELEMENTQUAKE, STATE_PRIORITY_USER, true);
    }
    if (state == 2)
    {

        obj.getVar("state").clear_vector();
        obj.getVar("state").push_vector(3);
        obj.sq_AddSetStatePacket(STATE_ELEMENTQUAKE, STATE_PRIORITY_USER, true);
    }



    if (state == 3)
    {
        obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
    }
}