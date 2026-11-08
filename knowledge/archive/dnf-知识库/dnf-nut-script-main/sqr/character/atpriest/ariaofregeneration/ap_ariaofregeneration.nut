function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_AriaOfRegeneration")
	appendage.sq_AddFunctionName("onEnd", "onEnd_appendage_AriaOfRegeneration")
	appendage.sq_AddFunctionName("getImmuneTypeDamageRate", "getImmuneTypeDamageRate_appendage_AriaOfRegeneration")
}

function onStart_appendage_AriaOfRegeneration(appendage)
{
	if (!appendage) return;
	local obj = appendage.getParent();
	if (!obj)
	{
		appendage.setValid(false);
		return;
	}
}

function getImmuneTypeDamageRate_appendage_AriaOfRegeneration(appendage, damageRate, attacker)
{
	if (!appendage)
		return damageRate;
	local obj = appendage.getParent();
	local sqrChr = sq_GetCNRDObjectToSQRCharacter(obj);
	local Rate = sq_GetIntData(sqrChr, SKILL_ARIA_OF_REGENERATION, 7);
	damageRate = damageRate - Rate / 10;
	return damageRate;
}

function onEnd_appendage_AriaOfRegeneration(appendage)
{
	if (!appendage) return;
	local obj = appendage.getParent();
}