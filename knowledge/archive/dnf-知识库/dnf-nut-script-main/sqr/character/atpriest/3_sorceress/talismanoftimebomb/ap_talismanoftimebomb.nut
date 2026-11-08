

function sq_AddFunctionName(appendage)

{

	appendage.sq_AddFunctionName("onStart" ,  "onStart_appendage_talismanoftimebomb")

	appendage.sq_AddFunctionName("proc" ,  "proc_appendage_talismanoftimebomb")

	appendage.sq_AddFunctionName("onEnd" ,  "onEnd_appendage_talismanoftimebomb")

}

function onStart_appendage_talismanoftimebomb(appendage)

{

	if(!appendage) return;

	local UncleBangValue1 =  appendage.getParent();

	local UncleBangValue2 =  appendage.getSource();

	local UncleBangValue2 =  sq_GetCNRDObjectToSQRCharacter(UncleBangValue2);

	if(!UncleBangValue2 || !UncleBangValue1)

	

{

appendage.setValid(false);

return;

	

}

}

function proc_appendage_talismanoftimebomb(appendage)

{

	if(!appendage) return;

	local UncleBangValue1 =  appendage.getParent();

	local UncleBangValue2 =  appendage.getSource();

	local UncleBangValue2 =  sq_GetCNRDObjectToSQRCharacter(UncleBangValue2);

	if(!UncleBangValue2 || !UncleBangValue1)

	

{

appendage.setValid(false);

return;

	

}

	local UncleBangValue4 =  -sq_GetIntData(UncleBangValue2 ,  SKILL_TALISMANOFTIMEBOMB ,  2);

	local UncleBangValue5 =  -sq_GetIntData(UncleBangValue2 ,  SKILL_TALISMANOFTIMEBOMB ,  3);

	local UncleBangValue6 =  appendage.sq_getChangeStatus("talismanoftimebomb");

	if(!UncleBangValue6)

	

{

UncleBangValue6 =  appendage.sq_AddChangeStatus("talismanoftimebomb" ,  UncleBangValue1 ,  UncleBangValue2 ,  0 ,  CHANGE_STATUS_TYPE_MOVE_SPEED ,  false ,  UncleBangValue4);

	

}

	if(UncleBangValue6)

	

{

UncleBangValue6.clearParameter();

UncleBangValue6.addParameter(CHANGE_STATUS_TYPE_MOVE_SPEED ,  false ,  UncleBangValue4.tofloat());

UncleBangValue6.addParameter(CHANGE_STATUS_TYPE_ATTACK_SPEED ,  false ,  UncleBangValue5.tofloat());

	

}

}

function onEnd_appendage_talismanoftimebomb(appendage)

{

	if(!appendage) return;

	local UncleBangValue1 =  appendage.getParent();

	local UncleBangValue2 =  appendage.getSource();

	local UncleBangValue2 =  sq_GetCNRDObjectToSQRCharacter(UncleBangValue2);

	appendage.sq_DeleteAppendages();

}

