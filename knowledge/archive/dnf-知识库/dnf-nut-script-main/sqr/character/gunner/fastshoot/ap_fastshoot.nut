function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_fastshoot")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_fastshoot")
	appendage.sq_AddFunctionName("onEnd", "onEnd_appendage_fastshoot")
}

function sq_AddEffect(appendage)
{
}

function proc_appendage_fastshoot(appendage)
{
	if(!appendage) return;
	local obj = appendage.getParent();
}

function onStart_appendage_fastshoot(appendage)
{
	if(!appendage) return;
	local obj = appendage.getParent();
	local sqrChr = sq_GetCNRDObjectToSQRCharacter(obj);

	local skillLevel = sqrChr.sq_GetSkillLevel(11);
	local physicalAttackBonus = sq_GetLevelData(sqrChr, 11, 1, skillLevel);
	local attackSpeed = sq_GetLevelData(sqrChr, 11, 2, skillLevel);
	local change_appendage = appendage.sq_getChangeStatus("fastshootp");
	if(!change_appendage)
	{
		change_appendage = appendage.sq_AddChangeStatus("fastshootp",obj, obj, 0, CHANGE_STATUS_TYPE_EQUIPMENT_PHYSICAL_ATTACK, true, physicalAttackBonus);
	}
	if(change_appendage)
	{
		change_appendage.clearParameter();
		change_appendage.addParameter(CHANGE_STATUS_TYPE_EQUIPMENT_PHYSICAL_ATTACK, true, physicalAttackBonus.tofloat());
		change_appendage.addParameter(CHANGE_STATUS_TYPE_ATTACK_SPEED, false, attackSpeed.tofloat());
	}

}

function onEnd_appendage_fastshoot(appendage)
{
	if(!appendage) return;
	local obj = appendage.getParent();
}
