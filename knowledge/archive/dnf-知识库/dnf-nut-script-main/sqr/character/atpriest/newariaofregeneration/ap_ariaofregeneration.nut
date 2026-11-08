
function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("getImmuneTypeDamageRate", "getImmuneTypeDamageRate_appendage_AriaOfRegeneration")
}



function getImmuneTypeDamageRate_appendage_AriaOfRegeneration(appendage, damageRate, attacker)
{
	if (!appendage)
		return damageRate;
	local obj = appendage.getParent();
	obj = sq_GetCNRDObjectToSQRCharacter(obj);
	local decreaseRate = obj.sq_GetIntData(SKILL_ARIA_OF_REGENERATION, 7);
	return damageRate - decreaseRate;
}

