//////////////////////////////////////////////////////////////////////////////////////////////////
//									
//////////////////////////////////////////////////////////////////////////////////////////////////








function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_firemark_enemy1")
	appendage.sq_AddFunctionName("proc", "proc_appendage_firemark_enemy1")
	appendage.sq_AddFunctionName("onEnd", "onEnd_appendage_firemark_enemy1")
}



function sq_AddEffect(appendage)
{
}



function onStart_appendage_firemark_enemy1(appendage)
{
	if(!appendage || !appendage.isValid())
	{
		return;
	}

	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();
	local sourceObj = sq_ObjectToSQRCharacter(sourceObj);
	if(!sourceObj || !parentObj)
	{
		appendage.setValid(false);
		return;
	}
	appendage.sq_AddEffectFront("passiveobject/character/thief/animation/firemark/firemarkb/firemark_markb_start.ani");
	local startTime = appendage.getTimer().Get();
	appendage.getVar("t").clear_vector();
	appendage.getVar("t").push_vector(startTime);
	local skill_level = sq_GetSkillLevel(sourceObj, SKILL_FIREMARK);
	local damage = sq_GetLevelData(sourceObj, SKILL_FIREMARK, 2, skill_level);
	local attackkInfo = sq_getNewAttackInfoPacket();
	attackkInfo.useWeapon = true;
	attackkInfo.powerRate = damage;
	attackkInfo.element = ENUM_ELEMENT_FIRE;
	attackkInfo.eType = ATTACKTYPE_MAGICAL;
		
	sq_SendHitObjectPacketByAttackInfo(sourceObj, parentObj, attackkInfo);
}



function proc_appendage_firemark_enemy1(appendage)
{
	if(!appendage || !appendage.isValid())
	{
		return;
	}

	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();
	local sourceObj = sq_ObjectToSQRCharacter(sourceObj);
	if(!sourceObj || !parentObj || parentObj.isDead())
	{
		appendage.setValid(false);
		return;
	}

	local currentTime = appendage.getTimer().Get();
	local startTime = appendage.getVar("t").get_vector(0);
	if(currentTime - startTime > sq_GetIntData(sourceObj, SKILL_FIREMARK, 1))
	{
		appendage.setValid(false);
		appendage.sq_DeleteEffectFront();
		local skill_level = sq_GetSkillLevel(sourceObj, SKILL_FIREMARK);
		local damage = sq_GetLevelData(sourceObj, SKILL_FIREMARK, 3, skill_level);
		local attackkInfo = sq_getNewAttackInfoPacket();
		attackkInfo.useWeapon = true;
		attackkInfo.powerRate = damage;
		attackkInfo.element = ENUM_ELEMENT_FIRE;
		attackkInfo.eType = ATTACKTYPE_MAGICAL;
		
		sq_SendHitObjectPacketByAttackInfo(sourceObj, parentObj, attackkInfo);
		appendage.getVar("t").set_vector(0, currentTime);
	}
}



function onEnd_appendage_firemark_enemy1(appendage)
{
	if(!appendage || !appendage.isValid())
	{
		return;
	}

	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();
	local sourceObj = sq_ObjectToSQRCharacter(sourceObj);
	if(!sourceObj || !parentObj)
	{
		appendage.setValid(false);
		return;
	}
	appendage.sq_DeleteEffectFront();
}

