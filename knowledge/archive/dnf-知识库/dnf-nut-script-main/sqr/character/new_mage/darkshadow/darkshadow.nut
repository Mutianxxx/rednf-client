function checkExecutableSkill_darkshadow(obj)  
{
	if (!obj) return false;

	local isUseSkill = obj.sq_IsUseSkill(SKILL_DARKSHADOW);
	if (isUseSkill) 
    {

        obj.getVar("state").clear_vector();
        obj.getVar("state").push_vector(0);
		obj.sq_AddSetStatePacket(STATE_DARKSHADOW, STATE_PRIORITY_USER, true);
		return true;
	}
	return false;
}


function checkCommandEnable_darkshadow(obj)
{

	return true;
}


function sendDarkShadowAllSummonMonster(obj)
{


    if (obj.getVar("flag").get_vector(0) == 1)
        return false;

    local maxNumber = sq_GetLevelData(obj, SKILL_DARKSHADOW, 0, sq_GetSkillLevel(obj, SKILL_DARKSHADOW) );

    obj.getVar("summonNumber").clear_vector();
    obj.getVar("summonNumber").push_vector(0);

    

    obj.getVar("flag").clear_vector();
    obj.getVar("flag").push_vector(1);

	local objectManager = obj.getObjectManager();

	for (local i = 0; i < objectManager.getCollisionObjectNumber(); i+=1)
	{

        local currNumber = obj.getVar("summonNumber").get_vector(0);

		local object = objectManager.getCollisionObject(i);

        if (object && !obj.isEnemy(object) && object.isInDamagableState(obj) && object.isObjectType(OBJECTTYPE_ACTIVE))
        {

            if (currNumber > maxNumber -1 )
                return false;

            obj.getVar("summonNumber").set_vector(0,currNumber + 1);

            local attackBonusRate = obj.sq_GetBonusRateWithPassive(SKILL_DARKSHADOW, STATE_DARKSHADOW, 1, 1.0);
            local size = sq_GetLevelData(obj, SKILL_DARKSHADOW, 2, sq_GetSkillLevel(obj, SKILL_DARKSHADOW) );
            local id = sq_GetObjectId(object);

            local waitTime = obj.sq_GetIntData(SKILL_DARKSHADOW, 0);
            local attackTime = obj.sq_GetIntData(SKILL_DARKSHADOW, 1);

            obj.sq_StartWrite();
            obj.sq_WriteDword(attackBonusRate);
            obj.sq_WriteDword(0);
            obj.sq_WriteDword(id);
            obj.sq_WriteDword(waitTime);
            obj.sq_WriteDword(attackTime);

            sq_SendCreatePassiveObjectPacketPos(obj, 24330, 0, object.getXPos(), object.getYPos(), 0);




        }
    }

}

function onSetState_DARKSHADOW(obj, state, datas, isResetTimer)
{

	obj.sq_StopMove();
    local state = obj.getVar("state").get_vector(0);

    if (state == 0)
    {


		local skillLevel = sq_GetSkillLevel(obj, SKILL_DARKSHADOW);
		local castTime  = sq_GetCastTime(obj, SKILL_DARKSHADOW, skillLevel);

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

function onProc_DARKSHADOW(obj)
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
            obj.sq_AddSetStatePacket(STATE_DARKSHADOW, STATE_PRIORITY_USER, true);
        }
    }
    
}

function onEndCurrentAni_DARKSHADOW(obj)
{
    local state = obj.getVar("state").get_vector(0);

    if (state == 1)
    {

        obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
    }

}

function onKeyFrameFlag_DARKSHADOW(obj,flagIndex)
{

    local state = obj.getVar("state").get_vector(0);

    if (state == 1)
    {

        if (flagIndex == 1)
        {

            sendDarkShadowAllSummonMonster(obj);
        }


    }

}






