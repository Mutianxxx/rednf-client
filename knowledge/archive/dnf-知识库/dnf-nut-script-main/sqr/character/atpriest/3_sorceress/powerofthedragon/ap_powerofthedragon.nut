

function sq_AddFunctionName(appendage)

{

	appendage.sq_AddFunctionName("onStart" ,  "onStart_appendage_powerofthedragon")

	appendage.sq_AddFunctionName("proc" ,  "proc_appendage_powerofthedragon")

	appendage.sq_AddFunctionName("onEnd" ,  "onEnd_appendage_powerofthedragon")

	appendage.sq_AddFunctionName("getImmuneTypeDamageRate" ,  "getImmuneTypeDamageRate_appendage_powerofthedragon")

}

function onStart_appendage_powerofthedragon(appendage)

{

	if(!appendage) return;

	local UncleBangValue1 =  appendage.getParent();

	local UncleBangValue2 =  appendage.getSource();

	local UncleBangValue1 =  sq_GetCNRDObjectToSQRCharacter(UncleBangValue1);

	if(!UncleBangValue2 || !UncleBangValue1)

	

{

appendage.setValid(false);

return;

	

}

}

function proc_appendage_powerofthedragon(appendage)

{

	if(!appendage) return;

	local UncleBangValue1 =  appendage.getParent();

	local UncleBangValue2 =  appendage.getSource();

	local UncleBangValue1 =  sq_GetCNRDObjectToSQRCharacter(UncleBangValue1);

	if(!UncleBangValue2 || !UncleBangValue1 || UncleBangValue1.isDead())

	

{

appendage.setValid(false);

return;

	

}

}

function onEnd_appendage_powerofthedragon(appendage)

{

	if(!appendage) return;

	appendage.sq_DeleteAppendages();

}

function getImmuneTypeDamageRate_appendage_powerofthedragon(appendage ,  damageRate ,  attacker)

{

	if(!appendage) return damageRate;

	local UncleBangValue1 =  appendage.getParent();

	local UncleBangValue2 =  appendage.getSource();

	local UncleBangValue1 =  sq_GetCNRDObjectToSQRCharacter(UncleBangValue1);

	if(!UncleBangValue2 || !UncleBangValue1)

	

{

appendage.setValid(false);

return damageRate;

	

}

	local UncleBangValue4 =  UncleBangValue1.sq_GetLevelData(SKILL_POWEROFDRAGON ,  3 ,  UncleBangValue1.sq_GetSkillLevel(SKILL_POWEROFDRAGON));

	damageRate =  damageRate - UncleBangValue4;

	return damageRate;

}

