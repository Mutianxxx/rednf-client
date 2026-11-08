

function onSetState_zmageAttack(obj, state, datas, isResetTimer)
{	
	if(!obj) return;
	if(isDollState(obj) && sq_getGrowType(obj) == 0){
		obj.sq_StopMove();
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_DOLL_MAD_ATK);
	}
	local speedUp = sq_GetLevelData(obj, 12, 1, obj.sq_GetSkillLevel(12))/1000+1;
	obj.sq_SetStaticSpeedInfo(SPEED_TYPE_ATTACK_SPEED, SPEED_TYPE_ATTACK_SPEED,SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, speedUp.tofloat(), speedUp.tofloat());
}


function onKeyFrameFlag_zmageAttack(obj,flagIndex)
{
	if(!obj)
		return false;

	local isMyControlObject = obj.sq_IsMyControlObject();

	// ????? ??????? ????
	if (isMyControlObject && flagIndex == 1 && sq_getGrowType(obj) == 0)
	{
		local attackBonusRate = obj.sq_GetBonusRateWithPassive(12, 23, SKL_LVL_COLUMN_IDX_0, 1.0);	// ?????1(%)
		local power = obj.sq_GetPowerWithPassive(12, 23, 4, SKL_LVL_COLUMN_IDX_0, 1.0);
		//local power = obj.sq_GetSkillPowerWithAttackBonusRate(12, 1, attackBonusRate);
		local upForce = sq_GetLevelData(obj, 12, 2, obj.sq_GetSkillLevel(12));

		obj.sq_StartWrite();
		//obj.sq_WriteWord(EARTHQUAKE_ROCK_MAX);
		obj.sq_WriteDword(attackBonusRate);	// attackBonusRate
		obj.sq_WriteDword(power);		// power
		obj.sq_WriteWord(upForce);		// upForce
		obj.sq_SendCreatePassiveObjectPacket(24201, 0, 120, 1, 0);
	}
	return true;
}

function onAfterSetState_zmageAttack(obj, state, datas, isResetTimer)
{
	if (!obj) return;
	if(CNSquirrelAppendage.sq_IsAppendAppendage(obj, "character/mage/avatar/ap_avatar.nut"))
	{
		local substate = obj.sq_GetVectorData(datas, 0); 
		local animation = null; 
		switch (substate) 
		{
			case 12:
				animation = setCurrentAnimation_avatar_eff(obj,"UpperSwing",true);
				break;
		}
		if(animation!=null)
			obj.setCurrentAnimation(animation); 
	}
}