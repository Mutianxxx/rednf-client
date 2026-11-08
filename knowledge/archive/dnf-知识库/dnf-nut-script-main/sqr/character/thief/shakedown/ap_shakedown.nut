function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_ShakeDown")
	appendage.sq_AddFunctionName("proc", "proc_appendage_ShakeDown")
	appendage.sq_AddFunctionName("onEnd", "onEnd_appendage_ShakeDown")
}


function sq_AddEffect(appendage)
{
}


function proc_appendage_ShakeDown(appendage)
{
	if(!appendage)
	{
		return;
	}

}


function onStart_appendage_ShakeDown(appendage)
{
	if(!appendage)
	{
		return;
	}

	local obj = appendage.getParent();
	local sqrChr = sq_GetCNRDObjectToSQRCharacter(obj);
	local skillLevel = sqrChr.sq_GetSkillLevel(SKILL_SHAKE_DOWN);

	local criticalDamage = sqrChr.sq_GetLevelData(SKILL_SHAKE_DOWN, 1, skillLevel);
	local changeAppendage = appendage.sq_getChangeStatus("ShakeDown");

	if(!changeAppendage)
	{
		changeAppendage = appendage.sq_AddChangeStatus("ShakeDown",obj, obj, 0, CHANGE_STATUS_TYPE_PHYSICAL_CRITICAL_DAMAGE_RATE, false, (criticalDamage.tofloat() / 10.0).tointeger());
	}

	else if(changeAppendage)
	{
		changeAppendage.clearParameter();
		changeAppendage.addParameter(CHANGE_STATUS_TYPE_PHYSICAL_CRITICAL_DAMAGE_RATE, false, criticalDamage.tofloat() / 10.0);
	}

}


function onEnd_appendage_ShakeDown(appendage)
{
	if(!appendage)
	{
		return;
	}

}

