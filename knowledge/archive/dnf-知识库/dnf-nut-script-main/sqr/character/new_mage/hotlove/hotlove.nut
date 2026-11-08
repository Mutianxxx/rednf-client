function checkExecutableSkill_hotlove(obj)  
{
	if (!obj) return false;
	local bobyNumber = obj.sq_GetIntData(SKILL_HOTLOVE, 5);
	if(bobyNumber < 0){
		bobyNumber = 0;
	}
	if (getBobyNumber(obj) >= bobyNumber)
	{
		local isUseSkill = obj.sq_IsUseSkill(SKILL_HOTLOVE);
		if (isUseSkill) 
		{
			obj.sq_AddSetStatePacket(STATE_HOTLOVE, STATE_PRIORITY_USER, true);
			return true;
		}
		return false;
	}else{
		playNoDollSound(obj);
	}
}


function checkCommandEnable_hotlove(obj)
{
	return (isOpenBobyBox(obj));
}

function onSetState_HOTLOVE(obj, state, datas, isResetTimer)
{
	if (!obj) return;
	obj.sq_StopMove();
	if(!isDollState(obj) )
	{
		obj.sq_SetCurrentAnimation(CUSTOM_ANI_HOTLOVE_BODY);
	}else{
		local ani = obj.getVar().GetAnimationMap("keepOut0", "character/mage/animation/zrr_ani/mad_keepoutstart.ani"); 
		obj.setCurrentAnimation(ani);
	}
	obj.getVar("flag").clear_vector();
	obj.getVar("flag").push_vector(0);
	obj.sq_SetStaticSpeedInfo(SPEED_TYPE_CAST_SPEED, SPEED_TYPE_CAST_SPEED,SPEED_VALUE_DEFAULT, SPEED_VALUE_DEFAULT, 1.0, 1.0);
}

function onKeyFrameFlag_HOTLOVE(obj,flagIndex)
{
	if (!obj) return;
	if (obj.getVar("flag").get_vector(0) == 0 )
	{
		obj.getVar("flag").clear_vector();
		obj.getVar("flag").push_vector(1);
		local attackBonusRate = obj.sq_GetBonusRateWithPassive(SKILL_HOTLOVE , STATE_HOTLOVE, 5, 1.0);
		obj.sq_StartWrite();
		obj.sq_WriteDword(attackBonusRate);	// attackBonusRate
		obj.sq_WriteDword(8);
		obj.sq_WriteDword( obj.sq_GetIntData(SKILL_HOTLOVE, 0) );
		obj.sq_WriteDword( sq_GetLevelData(obj, SKILL_HOTLOVE, 0, sq_GetSkillLevel(obj, SKILL_HOTLOVE) ) );
		obj.sq_WriteDword( obj.sq_GetIntData(SKILL_HOTLOVE, 1) );
		obj.sq_WriteDword( obj.sq_GetIntData(SKILL_HOTLOVE, 2) );
		obj.sq_WriteDword( obj.sq_GetIntData(SKILL_HOTLOVE, 3) );

		obj.sq_WriteDword( obj.sq_GetIntData(SKILL_HOTLOVE, 4) );//attack time
		obj.sq_WriteDword( sq_GetLevelData(obj, SKILL_HOTLOVE, 1, sq_GetSkillLevel(obj, SKILL_HOTLOVE) ) );//add time
		obj.sq_WriteDword( sq_GetLevelData(obj, SKILL_HOTLOVE, 2, sq_GetSkillLevel(obj, SKILL_HOTLOVE) ) );
		obj.sq_WriteDword( sq_GetLevelData(obj, SKILL_HOTLOVE, 3, sq_GetSkillLevel(obj, SKILL_HOTLOVE) ) );
		obj.sq_WriteDword( sq_GetLevelData(obj, SKILL_HOTLOVE, 4, sq_GetSkillLevel(obj, SKILL_HOTLOVE) ) );

		obj.sq_SendCreatePassiveObjectPacket(24364, 0, 42, 1, 60);
		local bobyNumber = obj.sq_GetIntData(SKILL_HOTLOVE, 5);
		if(bobyNumber < 0){
			bobyNumber = 0;
		}
		setBobyNumber(obj,getBobyNumber(obj) - bobyNumber );
		
	}
}

function onEndCurrentAni_HOTLOVE(obj)
{
	if (!obj) return;
	obj.sq_AddSetStatePacket(STATE_STAND, STATE_PRIORITY_USER, false);
}