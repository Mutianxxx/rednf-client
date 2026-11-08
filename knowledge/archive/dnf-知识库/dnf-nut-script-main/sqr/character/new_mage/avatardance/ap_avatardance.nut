
function sq_AddFunctionName(appendage)
{
	appendage.sq_AddFunctionName("proc", "proc_appendage_AVATARDANCE")
	appendage.sq_AddFunctionName("onStart", "onStart_appendage_AVATARDANCE")
}


function proc_appendage_AVATARDANCE(appendage)
{
	if(!appendage) {
		return;		
	}

	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();
				
	if(!sourceObj || !parentObj || sourceObj.getState() == STATE_STAND ) 
    {
		appendage.setValid(false);
		return;
	}
}



function onStart_appendage_AVATARDANCE(appendage)
{
	if(!appendage) {
		return;
	}
	
	local parentObj = appendage.getParent();
	local sourceObj = appendage.getSource();
				
	if(!sourceObj || !parentObj) {
		appendage.setValid(false);
		return;
	}	
}

