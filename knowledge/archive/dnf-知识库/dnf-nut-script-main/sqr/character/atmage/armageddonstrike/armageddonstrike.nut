function checkExecutableSkill_armageddonstrike(obj)  
{
	if (!obj) return false;

	local isUseSkill = obj.sq_IsUseSkill(SKILL_ARMAGEDDONSTRIKE);
	if (isUseSkill) {
        obj.getVar("state").clear_vector();
        obj.getVar("state").push_vector(0);
		obj.sq_AddSetStatePacket(STATE_ARMAGEDDONSTRIKE, STATE_PRIORITY_USER, true);
		return true;
	}
	return false;
}



function checkCommandEnable_armageddonstrike(obj)
{
	if(!obj)
		return false;
	return true;
}


function onSetState_ARMAGEDDONSTRIKE(obj, state, datas, isResetTimer)
{
	if (!obj) return;

	obj.sq_StopMove();
    local state = obj.getVar("state").get_vector(0);
	
	if (state == 0)
	{
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_YUANSU85_READY);
	}else if (state == 1){
        local high = 300;
		local attackBonusRate = obj.sq_GetBonusRateWithPassive(SKILL_ARMAGEDDONSTRIKE, STATE_ARMAGEDDONSTRIKE, 2, 1.0);
		local attackBonusRate2 = obj.sq_GetBonusRateWithPassive(SKILL_ARMAGEDDONSTRIKE, STATE_ARMAGEDDONSTRIKE, 1, 1.0);
		obj.sq_StartWrite();
		obj.sq_WriteDword(attackBonusRate);	// attackBonusRate
		obj.sq_WriteDword(39);	// attackBonusRate
		obj.sq_WriteDword(attackBonusRate2);	// attackBonusRate
		obj.sq_SendCreatePassiveObjectPacket(24357, 0, 0, 1, high);

		obj.sq_SetCurrentAnimation(CUSTOM_ANI_YUANSU85_DROP);
	}else if (state == 2){

		local attackBonusRate = obj.sq_GetBonusRateWithPassive(SKILL_ARMAGEDDONSTRIKE, STATE_ARMAGEDDONSTRIKE, 0, 1.0);
        sq_BinaryStartWrite();
        sq_BinaryWriteDword(attackBonusRate);	// attackBonusRate
        sq_BinaryWriteDword(41);
        sq_SendCreatePassiveObjectPacketPos(obj,24357, 0, obj.getXPos(), obj.getYPos()+1, 0);
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_YUANSU85_BOOM);
    }
}


// onEndCurrentAni
function onEndCurrentAni_ARMAGEDDONSTRIKE(obj)
{
	if (!obj) return;
    local state = obj.getVar("state").get_vector(0);
	if (state == 0){
        obj.getVar("state").clear_vector();
        obj.getVar("state").push_vector(1);
		obj.sq_AddSetStatePacket(STATE_ARMAGEDDONSTRIKE, STATE_PRIORITY_USER, true);
    }else if (state == 1){
        obj.getVar("state").clear_vector();
        obj.getVar("state").push_vector(2);
		obj.sq_AddSetStatePacket(STATE_ARMAGEDDONSTRIKE, STATE_PRIORITY_USER, true);
    }else if (state == 2){
		obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
    }
}






