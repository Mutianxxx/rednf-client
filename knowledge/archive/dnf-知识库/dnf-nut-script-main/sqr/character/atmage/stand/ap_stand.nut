
function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_ATMAGE_STAND")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_ATMAGE_STAND")
}
function sq_AddEffect(appendage)
{
}

function proc_appendage_ATMAGE_STAND(appendage)
{
	if(!appendage) {
		return;
	}

	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();
				
	if(!sourceObj || !parentObj) 
    {
		appendage.setValid(false);
		return;
	}
	local sqrChr = sq_GetCNRDObjectToSQRCharacter(parentObj);

	sqrChr.sq_SetCurrentAnimation(CUSTOM_ANI_BLOODIN);
}


function onStart_appendage_ATMAGE_STAND(appendage)
{
	if(!appendage) {
		return;
	}
	
}


