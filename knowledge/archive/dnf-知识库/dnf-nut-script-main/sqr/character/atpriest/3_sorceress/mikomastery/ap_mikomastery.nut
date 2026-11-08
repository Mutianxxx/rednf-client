

function sq_AddFunctionName(appendage)

{

	appendage.sq_AddFunctionName("onStart" ,  "onStart_appendage_mikomastery")

	appendage.sq_AddFunctionName("proc" ,  "proc_appendage_mikomastery")

	appendage.sq_AddFunctionName("onEnd" ,  "onEnd_appendage_mikomastery")

}

function onStart_appendage_mikomastery(appendage)

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

function proc_appendage_mikomastery(appendage)

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

function onEnd_appendage_mikomastery(appendage)

{

	if(!appendage) return;

	appendage.sq_DeleteAppendages();

}

