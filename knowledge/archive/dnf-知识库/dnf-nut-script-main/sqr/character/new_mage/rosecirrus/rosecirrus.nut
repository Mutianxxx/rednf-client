function checkExecutableSkill_rosecirrus(obj)  
{
	if (!obj) return false;

    local isUseSkill = obj.sq_IsUseSkill(SKILL_ROSECIRRUS);
    if (isUseSkill) 
    {
        obj.sq_AddSetStatePacket(STATE_ROSECIRRUS, STATE_PRIORITY_USER, true);
        return true;
    }
	return false;
}


function checkCommandEnable_rosecirrus(obj)
{
	if(!obj) return false;
	return true;
}

function startSkillCoolTime_ROSECIRRUS(obj, skillIndex, skillLevel, currentCoolTime)
{
	if(!obj) return currentCoolTime;
	local newCoolTime = coolTimeDec_Mage(obj,skillIndex,currentCoolTime);
	if(newCoolTime < 0)
	{
		newCoolTime = 0;
	}
	newCoolTime = newCoolTime.tointeger();
	return newCoolTime;
}

function onKeyFrameFlag_ROSECIRRUS(obj,flagIndex)
{
	if(!obj) return;
	if (flagIndex == 1 &&  obj.getVar("flag").get_vector(0) == 0 )
	{
		local level = sq_GetSkillLevel(obj, SKILL_ROSECIRRUS);		
		local damage = obj.sq_GetBonusRateWithPassive(SKILL_ROSECIRRUS , STATE_ROSECIRRUS, 0, 1.0);
		local maxNum = sq_GetLevelData(obj, SKILL_ROSECIRRUS, 1, level);
		local bloodProc = sq_GetLevelData(obj, SKILL_ROSECIRRUS, 2, level);
		local bloodleve = sq_GetLevelData(obj, SKILL_ROSECIRRUS, 3, level);
		local bloodtime = sq_GetLevelData(obj, SKILL_ROSECIRRUS, 4, level);
		local bloodRate = obj.sq_GetPowerWithPassive(SKILL_ROSECIRRUS, -1, 5, -1, 1.0);
		local len = obj.sq_GetIntData(SKILL_ROSECIRRUS, 0);
		obj.getVar("flag").clear_vector();
		obj.getVar("flag").push_vector(1);
		obj.sq_StartWrite();
		obj.sq_WriteDword(damage);	// attackBonusRate
		obj.sq_WriteDword(66);	// attackBonusRate
		obj.sq_WriteDword(1);	// attackBonusRate
		obj.sq_WriteDword(len);	// attackBonusRate
		obj.sq_WriteDword(maxNum);	// attackBonusRate
		obj.sq_WriteDword(bloodProc);
		obj.sq_WriteDword(bloodleve);
		obj.sq_WriteDword(bloodtime);
		obj.sq_WriteDword(bloodRate);
		obj.sq_SendCreatePassiveObjectPacket(24357, 0, len, 1, 0);
	}
}

function onSetState_ROSECIRRUS(obj, state, datas, isResetTimer)
{
	if(!obj) return;
	local damage = obj.sq_GetBonusRateWithPassive(SKILL_CIRRUSCUT , STATE_CIRRUSCUT, 0, 1.0);
	obj.sq_StopMove();
	if (!isDollState(obj))
	{
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_ROSECIRRUS);
	}else{
		local ani = obj.getVar().GetAnimationMap("rosecirrus", "character/mage/animation/zrr_ani/mad_rosecirrus.ani"); 
		obj.setCurrentAnimation(ani);
	}
	obj.getVar("flag").clear_vector();
	obj.getVar("flag").push_vector(0);
	obj.sq_SetStaticSpeedInfo(SPEED_TYPE_CAST_SPEED, SPEED_TYPE_CAST_SPEED,SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);

}

function onEndCurrentAni_ROSECIRRUS(obj)
{
	obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
}