function checkExecutableSkill_cirrusarea(obj)  
{
	if (!obj) return false;

	local isUseSkill = obj.sq_IsUseSkill(SKILL_CIRRUSAREA);
	if (isUseSkill) 
	{
		obj.sq_AddSetStatePacket(STATE_CIRRUSAREA, STATE_PRIORITY_USER, true);
		return true;
	}
	return false;
}


function checkCommandEnable_cirrusarea(obj)
{
	return true;
}

function onKeyFrameFlag_CIRRUSAREA(obj,flagIndex)
{
	if (flagIndex == 1 &&  obj.getVar("flag").get_vector(0) == 0 )
	{
		obj.getVar("flag").clear_vector();
		obj.getVar("flag").push_vector(1);
		local level = sq_GetSkillLevel(obj, SKILL_CIRRUSAREA);	
		local attackBonusRate = obj.sq_GetBonusRateWithPassive(SKILL_CIRRUSAREA, STATE_CIRRUSAREA, 0, 1.0);
		local attackBonusRate2 = obj.sq_GetBonusRateWithPassive(SKILL_CIRRUSAREA, STATE_CIRRUSAREA, 1, 1.0);
		local bloodProc = sq_GetLevelData(obj, SKILL_CIRRUSAREA, 2, level);
		local bloodleve = sq_GetLevelData(obj, SKILL_CIRRUSAREA, 3, level);
		local bloodtime = sq_GetLevelData(obj, SKILL_CIRRUSAREA, 4, level);
		local bloodRate = obj.sq_GetPowerWithPassive(SKILL_CIRRUSAREA, -1, 5, -1, 1.0);
		sq_BinaryStartWrite();
		sq_BinaryWriteDword(attackBonusRate);	// attackBonusRate
		sq_BinaryWriteDword(3);
		sq_BinaryWriteDword(obj.sq_GetIntData(SKILL_CIRRUSAREA, 1));
		sq_BinaryWriteDword(obj.sq_GetIntData(SKILL_CIRRUSAREA, 2));
		sq_BinaryWriteDword(attackBonusRate2);
		sq_BinaryWriteDword(bloodProc);
		sq_BinaryWriteDword(bloodleve);
		sq_BinaryWriteDword(bloodtime);
		sq_BinaryWriteDword(bloodRate);
		sq_BinaryWriteDword(obj.sq_GetIntData(SKILL_CIRRUSAREA, 0));
		obj.sq_SendCreatePassiveObjectPacket(24366, 0, obj.sq_GetIntData(SKILL_CIRRUSAREA, 0), 1, 0);
		obj.sq_SendCreatePassiveObjectPacket(12253, 0, obj.sq_GetIntData(SKILL_CIRRUSAREA, 0), 1, 0);
	}
}

function onSetState_CIRRUSAREA(obj, state, datas, isResetTimer)
{
	obj.sq_StopMove();
	if (!isDollState(obj) )
	{
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_CIRRUSAREA);
		sq_flashScreen(obj,240,200,160,102, sq_RGB(0,0,0), GRAPHICEFFECT_NONE, ENUM_DRAWLAYER_BOTTOM);
		obj.getVar("flag").clear_vector();
		obj.getVar("flag").push_vector(0);
	}else{
		local ani = obj.getVar().GetAnimationMap("cirrusarea", "character/mage/animation/zrr_ani/mad_thornvineholdstart.ani"); 
		obj.setCurrentAnimation(ani);
		obj.getVar("flag").clear_vector();
		obj.getVar("flag").push_vector(0);
		onKeyFrameFlag_CIRRUSAREA(obj,1);
	}
	obj.sq_SetStaticSpeedInfo(SPEED_TYPE_CAST_SPEED , SPEED_TYPE_CAST_SPEED , SPEED_VALUE_DEFAULT , SPEED_VALUE_DEFAULT , 1.0 , 1.0);
}

function onEndCurrentAni_CIRRUSAREA(obj)
{
	obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
}