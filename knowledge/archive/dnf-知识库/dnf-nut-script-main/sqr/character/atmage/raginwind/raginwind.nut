
function checkExecutableSkill_raginwind(obj)
{
	if (!obj)
		return false;
	
	local isUseSkill = obj.sq_IsUseSkill(SKILL_RAGINWIND);

	if (isUseSkill)
	{
        obj.getVar("state").clear_vector();
        obj.getVar("state").push_vector(0);
		obj.sq_AddSetStatePacket(STATE_RAGINWIND, STATE_PRIORITY_IGNORE_FORCE, false);
		return true;
	}	

	return false;
}

function onSetState_RAGINWIND(obj, state, datas, isResetTimer)
{
	obj.sq_StopMove();
    local state = obj.getVar("state").get_vector(0);
    local len = obj.sq_GetIntData(SKILL_RAGINWIND,2);
    local AsilaAr = obj.sq_GetIntData(SKILL_RAGINWIND,3);
    if (state == 0)
    {
        if(obj.isMyControlObject())
        {
            local attackBonusRate = obj.sq_GetBonusRateWithPassive(SKILL_RAGINWIND, STATE_RAGINWIND, 0, 1.0);
            obj.sq_StartWrite();
            obj.sq_WriteDword(attackBonusRate);	// attackBonusRate
            obj.sq_WriteDword(21);	// attackBonusRate
            obj.sq_SendCreatePassiveObjectPacket(24357, 0, len, 1, 0);
        }
        obj.sq_SetCurrentAnimation(CUSTOM_ANI_RAGINWIND_READY);
        obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED,
			SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);

    }else if (state == 1){
    
         local waitTime = obj.sq_GetIntData(SKILL_RAGINWIND,0);
         local atkTime = obj.sq_GetIntData(SKILL_RAGINWIND,1);
         local waitTime2 = obj.sq_GetIntData(SKILL_RAGINWIND,3);
         //local skillLevel = obj.sq_GetSkillLevel(SKILL_RAGINWIND);
         //print(AsilaAr+"a\n");
         if(obj.isMyControlObject())
        {

            local attackBonusRate = obj.sq_GetBonusRateWithPassive(SKILL_RAGINWIND, STATE_RAGINWIND, 1, 1.0);
            local attackBonusRate2 = obj.sq_GetBonusRateWithPassive(SKILL_RAGINWIND, STATE_RAGINWIND, 2, 1.0);
            obj.sq_StartWrite();
            obj.sq_WriteDword(attackBonusRate);	// attackBonusRate
            obj.sq_WriteDword(22);	// attackBonusRate
            obj.sq_WriteDword(waitTime + 100);	// attackBonusRate
            obj.sq_WriteDword(atkTime);	// attackBonusRate
            obj.sq_WriteDword(attackBonusRate2 ) ;	// attackBonusRate
            obj.sq_WriteDword(AsilaAr) ;
            obj.sq_SendCreatePassiveObjectPacket(24357, 0, len, 1, 0);
        }
        obj.sq_SetCurrentAnimation(CUSTOM_ANI_RAGINWIND_LOOP);
        obj.setTimeEvent(0,waitTime2,0,false);		
        obj.setTimeEvent(1,atkTime,0,true);		
        obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED,
			SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);
    }else if (state == 2){

//        obj.sq_SetShake(obj, 10, 120);
//		local attackBonusRate = obj.sq_GetBonusRateWithPassive(SKILL_RAGINWIND, STATE_RAGINWIND, 2, 1.0);
//		obj.sq_StartWrite();
//		obj.sq_WriteDword(attackBonusRate);	// attackBonusRate
//		obj.sq_WriteDword(23);	// attackBonusRate
//		obj.sq_SendCreatePassiveObjectPacket(24357, 0, len, 1, 0);

//        obj.sq_SetCurrentAnimation(CUSTOM_ANI_RAGINWIND_END);
//        obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED,
//			SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);
    }


}

function onTimeEvent_RAGINWIND(obj, timeEventIndex, timeEventCount)
{
    if(!obj.isMyControlObject())
        return false;
    local state = obj.getVar("state").get_vector(0);
    if (state == 1)
    {
        if (timeEventIndex == 0)
        {
            obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
//            obj.getVar("state").clear_vector();
//            obj.getVar("state").push_vector(2);
//            obj.sq_AddSetStatePacket(STATE_RAGINWIND , STATE_PRIORITY_USER, true);

        }else if (timeEventIndex == 1)
        {
            obj.sq_SetShake(obj, 2, 120);
        }
    }
}


function onEndCurrentAni_RAGINWIND(obj)
{
    if(!obj.isMyControlObject())
        return false;
    local state = obj.getVar("state").get_vector(0);
    if (state == 0)
    {
        obj.getVar("state").clear_vector();
        obj.getVar("state").push_vector(1);
		obj.sq_AddSetStatePacket(STATE_RAGINWIND, STATE_PRIORITY_IGNORE_FORCE, false);
    }else if (state == 1){
        obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
    }else if (state == 2){
        obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
    }
}

function checkCommandEnable_raginwind(obj)
{


	return true;

}