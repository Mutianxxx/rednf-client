//shake 2 150
//eventHrozien 
//start flash 240 80 160 102 0 0 0 bottom
//end  240 200 160 102 0 0 0 bottom
//passive flag 1 
//flash 0 120 300 127 255 255 255 bottom
//shake 8 300
function checkExecutableSkill_particlestrom(obj)  
{
	if (!obj) return false;
	local isUse = obj.sq_IsUseSkill(SKILL_PARTICLESTROM);

	if (isUse) {


			local pIntVec = sq_GetGlobalIntVector();
			sq_IntVectorClear(pIntVec);
			sq_IntVectorPush(pIntVec, 0);
			
			obj.addSetStatePacket(STATE_PARTICLESTROM , pIntVec, STATE_PRIORITY_FORCE, false, "");

		return true;
	}

	return false;
}

function checkCommandEnable_particlestrom(obj)
{
	if (!obj) return false;
	local state = obj.sq_GetState();
	return true;
}
//PARTICLESTROM

function onSetState_PARTICLESTROM(obj, state, datas, isResetTimer)
{
	if(!obj) return;

	obj.sq_StopMove();
	local state = obj.sq_GetVectorData(datas, 0);
	obj.setSkillSubState(state);
    if (state == 0)
    {

        obj.sq_SetCurrentAnimation(CUSTOM_ANI_PARTICLESTROM_CASTING );



        obj.sq_AddStateLayerAnimation(1, obj.sq_CreateCNRDAnimation("atanimation/als_ani/atdimensionbomb/dimensionbomb_cast_cast.ani"), 0, 0);

		local castTime = sq_GetCastTime(obj, SKILL_PARTICLESTROM, sq_GetSkillLevel(obj, SKILL_PARTICLESTROM)  );
		local animation = sq_GetCurrentAnimation(obj);
		local startTime = animation.getDelaySum(false);
		local speedRate = startTime.tofloat() / castTime.tofloat();
		obj.sq_SetStaticSpeedInfo(SPEED_TYPE_CAST_SPEED, SPEED_TYPE_CAST_SPEED,
			SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, speedRate, speedRate);

		sq_StartDrawCastGauge(obj, castTime, true);



    }else if (state == 1)
    {
        sq_SetMyShake(obj, 2, 400);
        local len = obj.sq_GetIntData(SKILL_PARTICLESTROM, 0);

		local leftPress = sq_IsKeyDown(OPTION_HOTKEY_MOVE_LEFT, ENUM_SUBKEY_TYPE_ALL);
		local rightPress = sq_IsKeyDown(OPTION_HOTKEY_MOVE_RIGHT, ENUM_SUBKEY_TYPE_ALL);

        if ( leftPress || rightPress)
        {
            len = obj.sq_GetIntData(SKILL_PARTICLESTROM, 1);
        }

        obj.sq_SetCurrentAnimation(CUSTOM_ANI_PARTICLESTROM_SHOOT);

        if (obj.isMyControlObject())
        {
            sq_flashScreen(obj,0,80,240,51, sq_RGB(255,255,255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);

            local power = obj.sq_GetPowerWithPassive(SKILL_PARTICLESTROM, STATE_PARTICLESTROM, 0, -1, 1.0);
    //        local hitC = sq_GetLevelData(obj, SKILL_PARTICLESTROM, 1, sq_GetSkillLevel(obj, SKILL_PARTICLESTROM) );
            obj.sq_StartWrite();
            obj.sq_WriteDword(power );	// attackBonusRate
            obj.sq_WriteDword(103);	// attackBonusRate
            obj.sq_WriteDword( obj.sq_GetIntData(SKILL_PARTICLESTROM, 5) );	// attackBonusRate

            obj.sq_SendCreatePassiveObjectPacket(24357, 0, len,1, obj.sq_GetIntData(SKILL_PARTICLESTROM, 3) );
        }

        setBreakSenseEnegry(obj,getBreakSenseEnegry(obj) + obj.sq_GetIntData(SKILL_PARTICLESTROM, 2) );


//        obj.sq_AddStateLayerAnimation(1, obj.sq_CreateCNRDAnimation("atanimation/als_ani/atdimensionlay/dimensionlay_circle_eff01.ani"), 0, 0);
    }else if (state == 2)
    {
        removeEventHorizen(obj);

        sq_SetMyShake(obj, 2, 400);
        local len = obj.sq_GetIntData(SKILL_PARTICLESTROM, 0);

        local leftPress = sq_IsKeyDown(OPTION_HOTKEY_MOVE_LEFT, ENUM_SUBKEY_TYPE_ALL);
        local rightPress = sq_IsKeyDown(OPTION_HOTKEY_MOVE_RIGHT, ENUM_SUBKEY_TYPE_ALL);

        if ( leftPress || rightPress)
        {
            len = obj.sq_GetIntData(SKILL_PARTICLESTROM, 1);
        }

        obj.sq_SetCurrentAnimation(CUSTOM_ANI_PARTICLESTROM_SHOOT);

        if (obj.isMyControlObject())
        {
            sq_flashScreen(obj,0,80,240,51, sq_RGB(255,255,255), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);

            local power = obj.sq_GetPowerWithPassive(SKILL_PARTICLESTROM, STATE_PARTICLESTROM, 1, -1, 1.0);
            obj.sq_StartWrite();
            obj.sq_WriteDword(power );	// attackBonusRate
            obj.sq_WriteDword(1003);	// attackBonusRate
            obj.sq_WriteDword( obj.sq_GetIntData(SKILL_PARTICLESTROM, 5) );	// attackBonusRate
            obj.sq_SendCreatePassiveObjectPacket(24357, 0, len,1, obj.sq_GetIntData(SKILL_PARTICLESTROM, 3) );
        }
    }
}

function onEndCurrentAni_PARTICLESTROM(obj)
{
    if (!obj.isMyControlObject())
        return false;

    local state = obj.getSkillSubState();
    if (state == 0)
    {
        if (!isEventHorizen(obj))
        {
			local pIntVec = sq_GetGlobalIntVector();
			sq_IntVectorClear(pIntVec);
			sq_IntVectorPush(pIntVec, 1);
			
			obj.addSetStatePacket(STATE_PARTICLESTROM , pIntVec, STATE_PRIORITY_FORCE, false, "");
        }else{
			local pIntVec = sq_GetGlobalIntVector();
			sq_IntVectorClear(pIntVec);
			sq_IntVectorPush(pIntVec, 2);
			
			obj.addSetStatePacket(STATE_PARTICLESTROM , pIntVec, STATE_PRIORITY_FORCE, false, "");
        }
    }else if (state == 1 || state == 2)
    {
		obj.sq_AddSetStatePacket(STATE_STAND , STATE_PRIORITY_USER, true);
    }
}