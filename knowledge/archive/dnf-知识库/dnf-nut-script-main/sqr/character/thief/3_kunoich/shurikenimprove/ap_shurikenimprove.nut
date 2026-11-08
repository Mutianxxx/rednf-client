//////////////////////////////////////////////////////////////////////////////////////////////////
//									
//////////////////////////////////////////////////////////////////////////////////////////////////








function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_shurikenimprove")
	appendage.sq_AddFunctionName("onEnd", "onEnd_appendage_shurikenimprove")
}



function sq_AddEffect(appendage)
{

}



function onStart_appendage_shurikenimprove(appendage)
{
	if(!appendage) return;
	local obj = appendage.getParent();
	local sqrChr = sq_GetCNRDObjectToSQRCharacter(obj);
	if(sqrChr.getWeaponSubType() == 5)
	{
		local skill_level = sq_GetSkillLevel(sqrChr, SKILL_SHURIKENIMPROVE);
		local EQUIPMENT_MAGICAL_ATTACK = sq_GetLevelData(sqrChr, SKILL_SHURIKENIMPROVE, 0, skill_level);
		local STUCK = sq_GetLevelData(sqrChr, SKILL_SHURIKENIMPROVE, 1, skill_level);
		EQUIPMENT_MAGICAL_ATTACK = EQUIPMENT_MAGICAL_ATTACK / 2;
		STUCK = STUCK / 2;
		local change_appendage = appendage.sq_getChangeStatus("shurikenimprove");

		if(!change_appendage)
		{
			change_appendage = appendage.sq_AddChangeStatus("shurikenimprove",obj, obj, 0, CHANGE_STATUS_TYPE_MAGICAL_ATTACK_BONUS, true, EQUIPMENT_MAGICAL_ATTACK);
			change_appendage = appendage.sq_AddChangeStatus("shurikenimprove",obj, obj, 0, CHANGE_STATUS_TYPE_STUCK, false, STUCK);
		}
		if(change_appendage) 
		{
			change_appendage.clearParameter();
			change_appendage.addParameter(CHANGE_STATUS_TYPE_MAGICAL_ATTACK_BONUS, true, EQUIPMENT_MAGICAL_ATTACK.tofloat());
			change_appendage.addParameter(CHANGE_STATUS_TYPE_STUCK, false, STUCK.tofloat());
		}
	}
}



function onEnd_appendage_shurikenimprove(appendage)
{
	if(!appendage) 
	{
		return;
	}


}

