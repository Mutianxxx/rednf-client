function checkExecutableSkill_lostcontrolwind(obj)  
{
	if (!obj) return false;

	local isUseSkill = obj.sq_IsUseSkill(SKILL_LOSTCONTROLWIND);
	if (isUseSkill) {
		obj.sq_AddSetStatePacket(STATE_LOSTCONTROLWIND, STATE_PRIORITY_USER, true);
		return true;
	}
	return false;
}



function checkCommandEnable_lostcontrolwind(obj)
{
	if(!obj)
		return false;

	return true;
}
function onKeyFrameFlag_LOSTCONTROLWIND(obj,flagIndex)
{
                if(!obj.isMyControlObject()) {
                    return;
                }
    if( obj.getVar("flag").get_vector(0) == 0)
    {

        obj.getVar("flag").clear_vector();
        obj.getVar("flag").push_vector(1);

        local disT = obj.sq_GetIntData(SKILL_LOSTCONTROLWIND, 0);
        local atkT = obj.sq_GetIntData(SKILL_LOSTCONTROLWIND, 1);
        local savT = obj.sq_GetIntData(SKILL_LOSTCONTROLWIND, 2);

		local attackBonusRate = obj.sq_GetBonusRateWithPassive(SKILL_LOSTCONTROLWIND, STATE_LOSTCONTROLWIND, 0, 1.0);

		local targetObj = findAngleTarget(obj, disT, 180, 100);
		if(targetObj) {
            disT = sq_Abs( targetObj.getXPos() - obj.getXPos() ) - 55;
        }
		obj.sq_StartWrite();
		obj.sq_WriteDword(attackBonusRate);	// attackBonusRate
		obj.sq_WriteDword(25);	// attackBonusRate
		obj.sq_WriteDword(disT);	// attackBonusRate
		obj.sq_WriteDword(atkT);	// attackBonusRate
		obj.sq_WriteDword(savT);	// attackBonusRate
		obj.sq_SendCreatePassiveObjectPacket(24357, 0, 55, 1, 0);
		obj.sq_PlaySound("R_MW_TORNADO"); 
    }
}
function onSetState_LOSTCONTROLWIND(obj, state, datas, isResetTimer)
{
	obj.sq_StopMove();

    obj.getVar("flag").clear_vector();
    obj.getVar("flag").push_vector(0);
	obj.sq_SetCurrentAnimation(CUSTOM_ANI_LOSTCONTROLWIND_BODY);

    obj.sq_SetStaticSpeedInfo(SPEED_TYPE_CAST_SPEED, SPEED_TYPE_CAST_SPEED,
        SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);
}

function onEndCurrentAni_LOSTCONTROLWIND(obj)
{
                if(!obj.isMyControlObject()) {
                    return;
                }
	obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
}