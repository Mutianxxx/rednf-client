function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("getImmuneTypeDamageRate", "getImmuneTypeDamageRate_appendage_Slothbody")
	appendage.sq_AddFunctionName("proc", "proc_appendage_Slothbody")
}


function getImmuneTypeDamageRate_appendage_Slothbody(appendage, damageRate, attacker)
{
	if (!appendage)
		return damageRate
	local obj = appendage.getParent()
	local obj = sq_GetCNRDObjectToSQRCharacter(obj)
	local skillLevel = obj.sq_GetSkillLevel(SKILL_SLOTHBODY)
	local Rate = obj.sq_GetLevelData(SKILL_SLOTHBODY, 1, skillLevel);

	damageRate = damageRate - Rate;
	return damageRate;
}

function proc_appendage_Slothbody(appendage)
{
	if(!appendage) {
		return;
	}

	local DamageMonster = appendage.getParent();
	local ChrMater = appendage.getSource();
	local ChrState = ChrMater.getState();
	local SqrChr = sq_GetCNRDObjectToSQRCharacter(ChrMater);
	local ChrSubState = SqrChr.getSkillSubState();
	local pAni = SqrChr.getCurrentAnimation();
	local frmIndex = sq_GetAnimationFrameIndex(pAni);

		if(ChrState != STATE_SLOTHBODY || ChrSubState != 0 )
		{
			appendage.setValid(false);
			return;
		}
}