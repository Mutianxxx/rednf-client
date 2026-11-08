
function checkExecutableSkill_IceArea(obj)
{

	if(!obj) return false;

	local b_useskill = obj.sq_IsUseSkill(SKILL_ICE_AREA);
	if(b_useskill) {
		obj.sq_AddSetStatePacket(STATE_ICE_AREA , STATE_PRIORITY_USER, false);
		return true;
	}	
	return false;

}

function checkCommandEnable_IceArea(obj)
{
	if(!obj)
		return false;
	if(sq_GetSkillLevel(obj, SKILL_ELEMENTAL_BOMBING) > 2){
		return true;
	}
	local state = obj.sq_GetState();
	if(state == STATE_ATTACK || state == STATE_STAND || state == STATE_DASH)
	{
		return true;
	}
	return false;
}

function startSkillCoolTime_IceArea(obj, skillIndex, skillLevel, currentCoolTime)
{
	local newCoolTime = currentCoolTime;
	
	if(SKILL_ICE_AREA == skillIndex)
	{
		local level		  = sq_GetSkillLevel(obj, SKILL_ICE_AREA);
		local addCoolTime = sq_GetIntData(obj, SKILL_ICE_AREA, 1, level);		
		newCoolTime = currentCoolTime + addCoolTime;		
	}
	return newCoolTime;	
}

function onSetState_IceArea(obj, state, datas, isResetTimer)
{
	if(!obj) return;

	obj.sq_StopMove();
	obj.sq_SetCurrentAnimation(CUSTOM_ANI_ICE_AREA);	
	
	// ????? ????? ???????? ????
	// ????? ????? ??????? ???????? ????? ???? ????.
	// ????? ???????? ???? ??????.
	local skillLevel = sq_GetSkillLevel(obj, SKILL_ICE_AREA);
	local castTime  = sq_GetCastTime(obj, SKILL_ICE_AREA, skillLevel);
	local animation = sq_GetCurrentAnimation(obj);
	local castAniTime = sq_GetFrameStartTime(animation, 2);
	local speedRate = castAniTime.tofloat() / castTime.tofloat();
	obj.sq_SetStaticSpeedInfo(SPEED_TYPE_CAST_SPEED, SPEED_TYPE_CAST_SPEED,
		SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, speedRate, speedRate);

	sq_StartDrawCastGauge(obj, castAniTime, true);
	addElementalChain_ATMage(obj, ENUM_ELEMENT_WATER);
obj.sq_SetStaticSpeedInfo(SPEED_TYPE_CAST_SPEED , SPEED_TYPE_CAST_SPEED , SPEED_VALUE_DEFAULT , SPEED_VALUE_DEFAULT , 1.0 , 1.0);
}

function prepareDraw_IceArea(obj)
{

	if(!obj) return;

	local substate = obj.getSkillSubState();

}

function onEndCurrentAni_IceArea(obj)
{
	if(!obj) return;
	
	obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
}

function onKeyFrameFlag_IceArea(obj, flagIndex)
{
	if(!obj) return true;
	
	if(flagIndex == 1) {		
		if(obj.isMyControlObject())
		{
			local level		  = sq_GetSkillLevel(obj, SKILL_ICE_AREA);
			local iceAreaRate = sq_GetIntData(obj, SKILL_ICE_AREA, 0, level);
			local skill_level = sq_GetSkillLevel(obj, SKILL_DARK_EYE);
			local sizeRate = obj.sq_GetLevelData(SKILL_DARK_EYE, 4, skill_level).tofloat() / 100.0;
			
			iceAreaRate = iceAreaRate * 0.01 + sizeRate; //100?????? ????
			
			local lifeTime	  = sq_GetLevelData(obj, SKILL_ICE_AREA, 0, level);			
			local iceRainCount= sq_GetLevelData(obj, SKILL_ICE_AREA, 2, level);
			local iceRate	  = sq_GetLevelData(obj, SKILL_ICE_AREA, 3, level);
			local iceLevel	  = sq_GetLevelData(obj, SKILL_ICE_AREA, 4, level);
			local iceTime	  = sq_GetLevelData(obj, SKILL_ICE_AREA, 5, level);		
					
			sq_BinaryStartWrite();
			sq_BinaryWriteFloat(iceAreaRate); // static : ?????? ???
			sq_BinaryWriteDword(lifeTime);		// 0.????e?
			
			sq_BinaryWriteDword(iceRainCount);	// 2.?????????? ???? ????
			sq_BinaryWriteDword(iceRate);		// 3.???? ???
			sq_BinaryWriteDword(iceLevel);		// 4.???? ????
			sq_BinaryWriteDword(iceTime);		// 5.???? ?e?			
				
			obj.sq_SendCreatePassiveObjectPacket(24225, 0, 260, 1, 0);
		}
		sq_EndDrawCastGauge(obj);
	}
	return true;

}
