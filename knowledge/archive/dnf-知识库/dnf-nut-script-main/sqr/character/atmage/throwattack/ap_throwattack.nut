
function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_THROWATTACK")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_THROWATTACK")
}


function proc_appendage_THROWATTACK(appendage)
{
	if(!appendage) {
		return;
	}

	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();
				
	if(!sourceObj || !parentObj || sourceObj.getState() == STATE_STAND) 
    {
		appendage.setValid(false);
		return;
	}
}


function onStart_appendage_THROWATTACK(appendage)
{
	if(!appendage) {
		return;
	}
	
}


