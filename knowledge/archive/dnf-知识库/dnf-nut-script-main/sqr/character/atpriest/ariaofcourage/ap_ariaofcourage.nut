function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_AriaOfCourage")
	appendage.sq_AddFunctionName("onEnd", "onEnd_appendage_AriaOfCourage")
	appendage.sq_AddFunctionName("getImmuneTypeDamageRate", "getImmuneTypeDamageRate_appendage_AriaOfCourage")
}

function onStart_appendage_AriaOfCourage(appendage)
{
	if (!appendage) return;
	local obj = appendage.getParent();
	if (!obj)
	{
		appendage.setValid(false);
		return;
	}
}

function getImmuneTypeDamageRate_appendage_AriaOfCourage(appendage, damageRate, attacker)
{
	if (!appendage)
		return damageRate;
	local obj = appendage.getParent();
	local sqrChr = sq_GetCNRDObjectToSQRCharacter(obj);
	local skillLevel = sqrChr.sq_GetSkillLevel(SKILL_ARIA_OF_COURAGE);
	local Rate = sqrChr.sq_GetLevelData(SKILL_ARIA_OF_COURAGE, 1, skillLevel);
	damageRate = damageRate - Rate / 10;
	return damageRate;
}

function onEnd_appendage_AriaOfCourage(appendage)
{
	if (!appendage) return;
	local obj = appendage.getParent();
}