//CUSTOM_ANI_WIND_STRIKE_BODY

function checkExecutableSkill_WindStrike(obj)  
{
	if (!obj) return false;
	local isUse = obj.sq_IsUseSkill(SKILL_WIND_STRIKE);

	if (isUse) {
        obj.getVar("state").clear_vector();
        if (obj.sq_GetSkillLevel(SKILL_BLOODOATH) > 0)
        {
            obj.getVar("state").push_vector(1);
        }else{
            obj.getVar("state").push_vector(0);
        }
		obj.sq_AddSetStatePacket(STATE_WIND_STRIKE , STATE_PRIORITY_USER, false);
		return true;
	}

	return false;
}


function checkCommandEnable_WindStrike(obj)
{
	return true;
}


function onSetState_WindStrike(obj, state, datas, isResetTimer)
{	
	if(!obj) return;
	obj.sq_StopMove();
    local state = obj.getVar("state").get_vector(0);
    if (state == 0)
    {
        //normal
        obj.sq_SetCurrentAnimation(CUSTOM_ANI_WIND_STRIKE);
        obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED,
			SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);
    }else if (state == 1)
    {
        //blood wind

        obj.sq_SetCurrentAnimation(CUSTOM_ANI_BLOODWINDSTRIKE_BODY);
        obj.sq_SetCurrentAttackInfo(ATTACKINFO_BLOODWINDSKRIKE);

		local attackBonusRate = obj.sq_GetBonusRateWithPassive(SKILL_WIND_STRIKE, STATE_WIND_STRIKE, SKL_LVL_COLUMN_IDX_0, 1.0);
		local power = obj.sq_GetPowerWithPassive(SKILL_WIND_STRIKE, STATE_WIND_STRIKE, SKL_LVL_COLUMN_IDX_1, SKL_LVL_COLUMN_IDX_0, 1.0);
		local upForce = obj.sq_GetLevelData(2);
        
        local attackInfo = sq_GetCurrentAttackInfo(obj);
        sq_SetCurrentAttackBonusRate(attackInfo, attackBonusRate);
        sq_SetCurrentAttackPower(attackInfo, power);
        sq_SetCurrentAttacknUpForce(attackInfo, upForce);
        obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED,
			SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);

    }else if (state == 2)
    {



        //windmaster add state
        obj.sq_SetCurrentAnimation(CUSTOM_ANI_WIND_STRIKE_BODY);
        obj.sq_SetCurrentAttackInfo(ATTACKINFO_WIND_STRIKE_UPPER);

        local rate = obj.sq_GetIntData(SKILL_WIND_STRIKE, 1);

        local lastRate = (100 + rate).tofloat() / 100.0;

		local attackBonusRate = obj.sq_GetBonusRateWithPassive(SKILL_WIND_STRIKE, STATE_WIND_STRIKE, 
        SKL_LVL_COLUMN_IDX_0, lastRate);

		local power = obj.sq_GetPowerWithPassive(SKILL_WIND_STRIKE, STATE_WIND_STRIKE, 
        SKL_LVL_COLUMN_IDX_1, SKL_LVL_COLUMN_IDX_0, lastRate);

		local upForce = obj.sq_GetLevelData(2);
        
        local attackInfo = sq_GetCurrentAttackInfo(obj);
        sq_SetCurrentAttackBonusRate(attackInfo, attackBonusRate);
        sq_SetCurrentAttackPower(attackInfo, power);
        sq_SetCurrentAttacknUpForce(attackInfo, upForce);
        obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED,
			SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);



    }else if (state == 3)
    {
        obj.sq_SetCurrentAnimation( CUSTOM_ANI_WIND_AIR_DASH );
        obj.getVar("len").clear_vector();
        obj.getVar("len").push_vector( obj.getXPos() );
        obj.getVar("len").push_vector( 300 );
        obj.getVar("len").push_vector( 250 );
        obj.getVar("len").push_vector( obj.getZPos()  );
    }
}


function onAttack_WindStrike(obj, damager, boundingBox, isStuck)
{
    local state = obj.getVar("state").get_vector(0);
    if (state == 1)
    {

//        setBloodValue(obj, obj.sq_GetIntData(SKILL_WIND_STRIKE, 0) );
        setCustomHitEffectBloodMageBlow(obj,damager);

        if (damager && !CNSquirrelAppendage.sq_IsAppendAppendage(damager,
            "character/atmage/append_bloodmage/ap_windstrike_upper.nut"))
        {
           local appendage = CNSquirrelAppendage.sq_AppendAppendage(damager, obj, SKILL_WIND_STRIKE, false, 
           "character/atmage/append_bloodmage/ap_windstrike_upper.nut", true);
            
        }

        if (obj)
        {
            local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, SKILL_WIND_STRIKE, false, 
            "character/atmage/append_bloodmage/ap_windstrike_upper_character.nut", true);
            
        }
    
    }

}

function onProc_WindStrike(obj)
{
    local state = obj.getVar("state").get_vector(0);
    if (state == 0)
    {
        if (obj.sq_GetSkillLevel(SKILL_STICKMASTER) > 0)
        {
            local pAni = obj.sq_GetCurrentAni();
            local frmIndex = obj.sq_GetCurrentFrameIndex(pAni);
            local currentT = sq_GetCurrentTime(pAni);

            if (frmIndex >= 4)
            {

                obj.setSkillCommandEnable(SKILL_WIND_STRIKE, true);

                local iEnterSkill = obj.sq_IsEnterSkill(SKILL_WIND_STRIKE);

                if (iEnterSkill != -1 || sq_IsKeyDown(OPTION_HOTKEY_ATTACK, ENUM_SUBKEY_TYPE_ALL))
                {

                    obj.getVar("state").clear_vector();
                    obj.getVar("state").push_vector(2);
                    obj.sq_AddSetStatePacket(STATE_WIND_STRIKE , STATE_PRIORITY_USER, false);

                }


            }
        }
    }else if (state == 3)
    {

        local startX = obj.getVar("len").get_vector(0);
        local maxD = obj.getVar("len").get_vector(1);
        local maxT = obj.getVar("len").get_vector(2);
        local startZ = obj.getZPos();//obj.getVar("len").get_vector(3);

        local pAni = obj.sq_GetCurrentAni();
        local currentT = sq_GetCurrentTime(pAni);

        if ( currentT < maxT )
        {
            local v1 = sq_GetAccel(0, maxD, currentT, maxT,true);
            local posX = sq_GetDistancePos(startX, obj.getDirection(), v1);

            if(obj.isMovablePos(posX, obj.getYPos()))
                obj.setCurrentPos(posX,obj.getYPos(),obj.getZPos() );
        }else{


            local appendage = CNSquirrelAppendage.sq_AppendAppendage(obj, obj, SKILL_RESONANCE, false,
            "character/atmage/jump/ap_jump.nut", true);

            obj.sq_IntVectClear();
            obj.sq_IntVectPush(1);
            obj.sq_IntVectPush(0);
            obj.sq_IntVectPush(0);
            obj.sq_AddSetStatePacket(STATE_JUMP, STATE_PRIORITY_USER, true);

        }


    }

}

function onEndCurrentAni_WindStrike(obj)
{
    local state = obj.getVar("state").get_vector(0);
    if (state == 0)
    {
        obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
    }else if (state == 1)
    {
        obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
    }else if (state == 2)
    {
        obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
    }

}


function onKeyFrameFlag_WindStrike(obj,flagIndex)
{
	if(!obj)
		return false;

	local isMyControlObject = obj.sq_IsMyControlObject();
    local state = obj.getVar("state").get_vector(0);
    if (state == 0)
    {
        if (isMyControlObject && flagIndex == 1)
        {
            
            local attackBonusRate = obj.sq_GetBonusRateWithPassive(SKILL_WIND_STRIKE, STATE_WIND_STRIKE, SKL_LVL_COLUMN_IDX_0, 1.0);
            local power = obj.sq_GetPowerWithPassive(SKILL_WIND_STRIKE, STATE_WIND_STRIKE, SKL_LVL_COLUMN_IDX_1, SKL_LVL_COLUMN_IDX_0, 1.0);
            local upForce = obj.sq_GetLevelData(2);
                    
                    
            obj.sq_StartWrite();
            obj.sq_WriteDword(attackBonusRate);	// attackBonusRate
            obj.sq_WriteDword(power);		// power
            obj.sq_WriteWord(upForce);		// upForce
            obj.sq_SendCreatePassiveObjectPacket(24201, 0, 120, 1, 0);
        }
        return true;
    }
}
