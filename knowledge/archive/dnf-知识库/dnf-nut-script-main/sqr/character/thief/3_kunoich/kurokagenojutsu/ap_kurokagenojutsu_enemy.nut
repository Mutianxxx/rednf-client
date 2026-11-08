//////////////////////////////////////////////////////////////////////////////////////////////////
//									
//////////////////////////////////////////////////////////////////////////////////////////////////








function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_kurokagenojutsu_enemy")
	appendage.sq_AddFunctionName("proc", "proc_appendage_kurokagenojutsu_enemy")
	appendage.sq_AddFunctionName("onEnd", "onEnd_appendage_kurokagenojutsu_enemy")
	appendage.sq_AddFunctionName("getImmuneTypeDamageRate", "getImmuneTypeDamageRate_appendage_kurokagenojutsu_enemy")
}



function sq_AddEffect(appendage)
{
}



function onStart_appendage_kurokagenojutsu_enemy(appendage)
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
	appendage.sq_AddEffectFront("character/thief/effect/animation/kurokagenojutsu/kurokagenojutsu_targetstart.ani");
	local startTime = appendage.getTimer().Get();
	appendage.getVar("t").clear_vector();
	appendage.getVar("t").push_vector(startTime);
}



function proc_appendage_kurokagenojutsu_enemy(appendage)
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
	if(currentTime - startTime > sourceObj.sq_GetIntData(SKILL_KUROKAGENOJUTSU, 0))
	{
		appendage.setValid(false);
		appendage.sq_DeleteEffectFront();
		appendage.getVar("t").set_vector(0, currentTime);
	}
}



function onEnd_appendage_kurokagenojutsu_enemy(appendage)
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



function getImmuneTypeDamageRate_appendage_kurokagenojutsu_enemy(appendage, damageRate, attacker)
{
	if(!appendage)
		return damageRate;

	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();
	local sourceObj = sq_ObjectToSQRCharacter(sourceObj);
	if(!sourceObj || !parentObj)
	{
		appendage.setValid(false);
		return damageRate;
	}
	local var = appendage.getVar();
	if(!var)
		return damageRate;
	local skill_level = sq_GetSkillLevel(sourceObj, SKILL_KUROKAGENOJUTSU);
	local decreaseRate = -sourceObj.sq_GetLevelData(SKILL_KUROKAGENOJUTSU, 0, skill_level);
	damageRate = damageRate - decreaseRate;
		return damageRate;
}

