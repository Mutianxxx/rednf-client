//////////////////////////////////////////////////////////////////////////////////////////////////
//									
//////////////////////////////////////////////////////////////////////////////////////////////////








function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_swordofkusanagi")
	appendage.sq_AddFunctionName("proc", "proc_appendage_swordofkusanagi")
	appendage.sq_AddFunctionName("onEnd", "onEnd_appendage_swordofkusanagi")
}



function sq_AddEffect(appendage)
{

}



function onStart_appendage_swordofkusanagi(appendage)
{
	if(!appendage) return;

	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();
	local parentObj = sq_GetCNRDObjectToSQRCharacter(parentObj);
	if(!sourceObj || !parentObj)
	{
		appendage.setValid(false);
		return;
	}
}



function proc_appendage_swordofkusanagi(appendage)
{
	if(!appendage) return;

	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();
	local parentObj = sq_GetCNRDObjectToSQRCharacter(parentObj);
	if(!sourceObj || !parentObj || parentObj.isDead())
	{
		appendage.setValid(false);
		return;
	}
	parentObj.setSkillCommandEnable(SKILL_SWORDOFKUSANAGI, true);
	if(parentObj.sq_IsEnterSkill(SKILL_SWORDOFKUSANAGI) != -1)
	{
		parentObj.sq_StartWrite();
		parentObj.sq_WriteDword(63);
		parentObj.sq_SendCreatePassiveObjectPacket(24356, 0, 0, 0, 0);
		appendage.setValid(false);
	}
}



function onEnd_appendage_swordofkusanagi(appendage)
{
	if(!appendage) return;

	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();
	local parentObj = sq_GetCNRDObjectToSQRCharacter(parentObj);
	if(!sourceObj || !parentObj)
	{
		appendage.setValid(false);
		return;
	}
	parentObj.sq_StartWrite();
	parentObj.sq_WriteDword(63);
	parentObj.sq_SendCreatePassiveObjectPacket(24356, 0, 0, 0, 0);
}

