
// ?????????? ?????? ??????
function checkExecutableSkill_Concentrate(obj)
{
	if (!obj) return false;

	local isUseSkill = obj.sq_IsUseSkill(SKILL_CONCENTRATE_EX);
	if (isUseSkill)
	{
		obj.sq_AddSetStatePacket(STATE_CONCENTRATE_EX, STATE_PRIORITY_IGNORE_FORCE, false);		
		return true;
	}	

	return false;
}


function checkCommandEnable_Concentrate(obj)
{
	if(!obj) return false;
	if(sq_GetSkillLevel(obj, SKILL_ELEMENTAL_BOMBING) > 4){
		return true;
	}
	local state = obj.sq_GetState();
	if(state == STATE_ATTACK || state == STATE_STAND || state == STATE_DASH)
	{
		return true;
	}
	return false;
}

// state?? ??????? ó?????? ?????? ????.
// ???? ??????? ????????. 
function onSetState_Concentrate(obj, state, datas, isResetTimer)
{	
	if (!obj) return;
	
	obj.sq_SetStaticMoveInfo(0, 0, 0, false);
	obj.sq_SetStaticMoveInfo(1, 0, 0, false);
	
	
	// ??????? ??????? 4??? ??????????.
	local element = obj.getThrowElement();
	addElementalChain_ATMage(obj, element);
		
		
	obj.sq_SetCurrentAnimation(CUSTOM_ANI_CONCENTRATE_EX);		

	// ???? ?÷???	
	obj.sq_PlaySound("MW_CONCENTRATE");
obj.sq_SetStaticSpeedInfo(SPEED_TYPE_CAST_SPEED , SPEED_TYPE_CAST_SPEED , SPEED_VALUE_DEFAULT , SPEED_VALUE_DEFAULT , 1.0 , 1.0);
}


// ?????????? ??????.
function onEndCurrentAni_Concentrate(obj)
{
	if (!obj) return;

	if (obj.sq_IsMyControlObject())
		obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
}	
	

function onEndState_Concentrate(obj, newState)
{
	if (!obj) return;
}


// ????? ???? ??ü?? ???????.
function onKeyFrameFlag_Concentrate(obj, flagIndex)
{
	if (!obj) return false;
	
	if (flagIndex == 1)
	{
		obj.sq_PlaySound("BREAKING_RUSH");
		if (obj.sq_IsMyControlObject())
		{
			local level = obj.sq_GetSkillLevel(SKILL_CONCENTRATE_EX);
			
			// ???????????
			// ???????? ???? ?????? ??????? ????. (ATConcentrate.ptl)
			local maxBoundNumber = obj.sq_GetIntData(SKILL_CONCENTRATE_EX, 0);
			
			// ???? ?????? ?????
			local smallExpBonusRate = obj.sq_GetBonusRateWithPassive(SKILL_CONCENTRATE_EX, STATE_CONCENTRATE_EX, 0, 1.0);
			local bigExpBonusRate = obj.sq_GetBonusRateWithPassive(SKILL_CONCENTRATE_EX, STATE_CONCENTRATE_EX, 1, 1.0);
			local bigExpSizeRate = obj.sq_GetLevelData(SKILL_CONCENTRATE_EX, 2, level);
			
			
			// ????? ?????? ???????
			
			obj.sq_StartWrite();
			obj.sq_WriteWord(maxBoundNumber);
			obj.sq_WriteDword(smallExpBonusRate);
			obj.sq_WriteDword(bigExpBonusRate);
			obj.sq_WriteWord(bigExpSizeRate);
			obj.sq_WriteByte(obj.getThrowElement());
			obj.sq_SendCreatePassiveObjectPacket(24286, 0, 73, 1, 47);
		}
	}
	
	return true;
}


