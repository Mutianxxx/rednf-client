function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_weaponguard")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_weaponguard")
	appendage.sq_AddFunctionName("onEnd", "onEnd_appendage_weaponguard")
	appendage.sq_AddFunctionName("getImmuneTypeDamageRate", "getImmuneTypeDamageRate_appendage_weaponguard")
}

function proc_appendage_weaponguard(appendage)
{
	if(!appendage) return;
	local obj = appendage.getParent();
}

function onStart_appendage_weaponguard(appendage)
{
	if(!appendage) return;
	local obj = appendage.getParent();
}

function getImmuneTypeDamageRate_appendage_weaponguard(appendage, damageRate, attacker)
{
	if (!appendage) return damageRate;

	local obj = appendage.getParent();
	local sqrChr = sq_GetCNRDObjectToSQRCharacter(obj);
	local skillLevel = sqrChr.sq_GetSkillLevel(SKILL_WEAPON_GUARD);
	local Rate = sqrChr.sq_GetLevelData(SKILL_WEAPON_GUARD, 2, skillLevel) / 10;
	damageRate = damageRate - Rate ;
	//print("getImmuneTypeDamageRate : " + damageRate);
	return damageRate;
}

function onEnd_appendage_weaponguard(appendage)
{
	if(!appendage) return;
	local obj = appendage.getParent();
}

