function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_dieji")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_dieji")
	appendage.sq_AddFunctionName("onEnd", "onEnd_appendage_dieji")
	appendage.sq_AddFunctionName("onAttackParent", "onAttackParent_appendage_dieji")
}

function sq_AddEffect(appendage)
{
}

function proc_appendage_dieji(appendage)
{
	if(!appendage) return;
	local obj = appendage.getParent();
}

function onStart_appendage_dieji(appendage)
{
	if(!appendage) return;
	local obj = appendage.getParent();
}

function onEnd_appendage_dieji(appendage)
{
	if(!appendage) return;
	local obj = appendage.getParent();
}

function onAttackParent_appendage_dieji(appendage, realAttacker, damager, boundingBox, isStuck)
{
	if(!appendage) return;
	local obj = appendage.getParent();
	local sqrChr = sq_GetCNRDObjectToSQRCharacter(obj);
	local skillLevel = sqrChr.sq_GetSkillLevel(SKILL_DIE_JI);
	local base = 100;
	local prob = sq_GetLevelData(sqrChr, SKILL_DIE_JI, 0, skillLevel);
	local random = sq_getRandom(0, base);
	if(prob >= random)
	{
		local powerAdd = sq_GetLevelData(sqrChr, SKILL_DIE_JI, 1, skillLevel);
		local powerAddTime = sq_GetLevelData(sqrChr, SKILL_DIE_JI, 2, skillLevel);
		local hitRecoveryAdd = sq_GetLevelData(sqrChr, SKILL_DIE_JI, 3, skillLevel);
		local hitRecoveryAddTime = sq_GetLevelData(sqrChr, SKILL_DIE_JI, 4, skillLevel);
		local powerAddApd = sq_CreateChangeStatus(CHANGE_STATUS_TYPE_EQUIPMENT_PHYSICAL_ATTACK, true, powerAdd.tofloat() , powerAddTime);
		powerAddApd.sq_Append(obj,obj);
		local hitRecoveryAddApd = sq_CreateChangeStatus(CHANGE_STATUS_TYPE_HIT_RECOVERY, true, hitRecoveryAdd.tofloat() , hitRecoveryAddTime);
		hitRecoveryAddApd.sq_Append(obj,obj);
	}
}


